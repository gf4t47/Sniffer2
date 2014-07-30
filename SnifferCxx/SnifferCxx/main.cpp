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
#include "initializer/HypothesisInitializer.h"
#include "initializer/MapBuilder.h"
#include "backwrad/BackwardChecking.h"
#include "model/Map3D.h"
#include "model/Cells.h"
#include "filesystem/MessageBuilder.h"
#include "filesystem/hypothesis.pb.h"

using namespace std;
using namespace initializer;
using namespace Model;


const string strDetection = "detection";
const string strTime = "time";
const string strLeak = "leak";
const string strLocation = "location";
const string strConcentration = "concentration";
const string strRepeat = "repeat";

struct detection {
    size_t time_;
    vector<Leak> detected_;
};


shared_ptr<vector<detection>> load(string filename) {
    using boost::property_tree::ptree;
    using boost::lexical_cast;
    
    ptree pt;
    read_json(filename, pt);
    
    auto dect_vec = make_shared<vector<detection>>();
    
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
    
    return dect_vec;
}

int main(int argc, const char * argv[])
{
    //load map
    MapBuilder mb(argv[1]);
    auto map = mb.build();
    
    //load hypotheses
    HypothesisInitializer hypI(argv[2]);
    auto alg = hypI.getCheckingAlg();
    auto hyps = hypI.getHyptheses();
    
    //load detection
    auto dect_vect = load(argv[3]);
    
    vector<shared_ptr<vector<Hypothesis>>> hyps_hist;
    hyps_hist.push_back(hyps);
    for (auto dect : *dect_vect)
    {
        hyps = alg->updateHypotheses(*hyps, *map, dect.time_, dect.detected_);
        hyps_hist.push_back(hyps);
    }

	// Write the new address book back to disk.
	auto msg = Filesystem::MessageBuilder::buildMessage(hyps_hist);
	fstream output(argv[4], ios::out | ios::trunc | ios::binary);
	if (!msg->SerializeToOstream(&output)) {
		cerr << "Failed to write address book." << endl;
		return -1;
	}
        
    return 0;
}

