//
//  main.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <thread>
#include "initializer/HypothesisInitializer.h"
#include "initializer/MapBuilder.h"
#include "backwrad/BackwardChecking.h"
#include "forward/ForwardChecking.h"
#include "model/Map3D.h"
#include "model/Cells.h"
#include "filesystem/MessageBuilder.h"
#include "filesystem/hypothesis.pb.h"

using namespace std;
using namespace Model;

const string strDetection = "detection";
const string strTime = "time";
const string strLeak = "leak";
const string strLocation = "location";
const string strConcentration = "concentration";
const string strRepeat = "repeat";
const string strMultithread = "multithread";

struct detection {
    size_t time_;
    vector<Leak> detected_;
};


tuple<shared_ptr<vector<detection>>, bool> load(string filename) {
    using boost::property_tree::ptree;
    using boost::lexical_cast;
    
    ptree pt;
    read_json(filename, pt);
    
    auto dect_vec = make_shared<vector<detection>>();
    
	auto multithread = pt.get<bool>(strMultithread);

    for (auto dect_node : pt.get_child(strDetection)) {
        auto dect = dect_node.second;
        
        detection detection;
        
        detection.time_ = dect.get<size_t>(strTime);
        for (auto leak_node : dect.get_child(strLeak)) {
            auto leak = leak_node.second;
            
            Leak detected;
            auto location = leak.get_child(strLocation);
            transform(location.begin(), location.end(), detected.location_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
            detected.concentration_ = leak.get<mtn_t>(strConcentration);
            
            detection.detected_.push_back(detected);
        }
        
        auto repeat = dect.get<size_t>(strRepeat);
        for (auto i = 0; i < repeat; i++) {
            dect_vec->push_back(detection);
        }
    }
    
    return make_tuple(dect_vec, multithread);
}


void init_log(string filename)
{
	namespace logging = boost::log;
	namespace keywords = boost::log::keywords;
	namespace sinks = boost::log::sinks;

	logging::add_file_log
		(
		keywords::file_name = filename,
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::format = "[%TimeStamp%]: %Message%"
		);

	logging::add_common_attributes();

	logging::core::get()->set_filter
		(
		logging::trivial::severity >= logging::trivial::info
		);
}

int main(int argc, const char * argv[])
{
	using namespace initializer;
	using namespace Forward;

	init_log(argv[6]);

    //load map
    MapBuilder mb(argv[1]);
    auto map = mb.build();
    
    //load hypotheses
    HypothesisInitializer hypI(argv[2]);
    auto backward = hypI.getBackwardAlg();
	auto forward = hypI.getForwardAlg();
    auto hyps = hypI.getHyptheses();
    
    //load detection
	shared_ptr<vector<detection>> dect_vect;
	bool multiple_thread;
    tie(dect_vect, multiple_thread) = load(argv[3]);

    //calculation
    vector<shared_ptr<vector<Hypothesis>>> hyps_hist;
    hyps_hist.push_back(hyps);
    if (!multiple_thread) {
        for (auto dect : *dect_vect)
        {
            backward->updateHypotheses(*hyps, *map, dect.detected_, dect.time_, forward);
        }
    }
	else {
		boost::tribool forward_alive = true;
		std::thread forward_task(&ForwardChecking::work, forward, hyps, std::ref(*map), std::ref(forward_alive), std::ref(hyps_hist));
		forward_task.detach();

		for (auto dect : *dect_vect)
		{
			std::chrono::milliseconds dura(dect.time_ * 100);
			std::this_thread::sleep_for(dura);
			backward->updateHypotheses(*hyps, *map, dect.detected_, dect.time_, nullptr);
		}
		forward_alive = false;
	}
    
    //message output
    auto map_msg = Filesystem::MessageBuilder::buildMessage(*map);
    fstream map_out(argv[5], ios::out | ios::trunc | ios::binary);
    if (!map_msg->SerializeToOstream(&map_out)) {
        cerr << "Failed to write msg" << endl;
		return -1;
    }

	auto mtn_msg = Filesystem::MessageBuilder::buildMessage(hyps_hist);
	fstream mtn_out(argv[4], ios::out | ios::trunc | ios::binary);
	if (!mtn_msg->SerializeToOstream(&mtn_out)) {
		cerr << "Failed to write msg" << endl;
		return -1;
	}
        
    return 0;
}

