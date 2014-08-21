//
//  main.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <thread>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

//init
#include "initializer/HypothesisInitializer.h"
#include "initializer/MapBuilder.h"
#include "initializer/DetectionInitializer.h"

//calc
#include "backward/BackwardChecking.h"
#include "forward/ForwardChecking.h"
#include "backward/CandidateGenerator.h"
#include "model/Hypothesis.h"

//message
#include "protomsg/MessageBuilder.h"
#include "protomsg/hypothesis.pb.h"
#include "protomsg/dect.pb.h"

using namespace std;
using namespace Initializer;
using namespace Model;

int main(int argc, const char * argv[])
{
	using namespace Forward;
    using namespace Backward;
    
    if (argc < 8) {
        cerr << argv[0] << " Missing some argument to indicate input files" << endl;
        return -1;
    }
    
    string map_cfg = argv[1];
    string hyps_cfg = argv[2];
    string dect_cfg = argv[3];
    string mtn_output = argv[4];
    string map_output = argv[5];
    string dect_output = argv[6];
    string can_output= argv[7];

    //load map
    MapBuilder mb(map_cfg);
    auto map = mb.build();

	//load hypotheses
	HypothesisInitializer hypI(hyps_cfg);
	auto backward = hypI.getBackwardAlg();
	auto forward = hypI.getForwardAlg();
	auto hyps = hypI.getHyptheses();
    
    //load detection
    DetectionInitializer dectI(dect_cfg);
    auto dect_vect = dectI.getDetections();
	auto multiple_thread = dectI.beMultiplethread();
    auto can_vect = make_shared<vector<Detection>>();

    //calculation
    vector<shared_ptr<vector<Hypothesis>>> hyps_hist;
    hyps_hist.push_back(hyps);
    if (!multiple_thread) {
        for (auto const & dect : *dect_vect)
        {
            hyps = backward->updateHypotheses(*hyps, *map, dect.detected_, dect.time_, forward);
            hyps_hist.push_back(hyps);
        }
        
		CandidateGenerator cg(*forward, *backward, *map);
        auto auto_movement = dectI.getAutoMovementInfo();
        if (auto_movement) {
            while (Hypothesis::getMaxProbHyp(*hyps).getProbability() < auto_movement->threshold_) {
				auto max_can = cg.generateCandidate(dect_vect->back().detected_.back().location_, auto_movement->time_, auto_movement->distance_, *hyps);
                cout << "max candidate : " << max_can.location_ << " = " << max_can.concentration_ << endl;

				Detection next_dect;
				next_dect.time_ = auto_movement->time_;
                next_dect.detected_.push_back(Candidate(max_can.location_, 1.0));
                dect_vect->push_back(next_dect);
                
                hyps = backward->updateHypotheses(*hyps, *map, next_dect.detected_, next_dect.time_, forward);
                hyps_hist.push_back(hyps);
            }
        }
    }
	else {
		//boost::tribool forward_alive = true;
		//std::thread forward_task(&ForwardChecking::work, forward, hyps, std::ref(*map), std::ref(forward_alive), std::ref(hyps_hist));
		//forward_task.detach();

		//for (auto const & dect : *dect_vect)
		//{
		//	std::chrono::milliseconds dura(dect.time_ * 100);
		//	std::this_thread::sleep_for(dura);
		//	backward->updateHypotheses(*hyps, *map, dect.detected_, dect.time_, nullptr);
		//}
		//forward_alive = false;
	}
    
    //message output
    auto map_msg = ProtoMsg::MessageBuilder::buildMessage(*map);
    fstream map_out(map_output, ios::out | ios::trunc | ios::binary);
    if (!map_msg->SerializeToOstream(&map_out)) {
        cerr << "Failed to write msg" << endl;
		return -1;
    }
    
    auto dect_msg = ProtoMsg::MessageBuilder::buildMessage(*dect_vect);
    fstream dect_out(dect_output, ios::out | ios::trunc | ios::binary);
    if (!dect_msg->SerializeToOstream(&dect_out)) {
        cerr << "Failed to write msg" << endl;
		return -1;
    }
    
    auto can_msg = ProtoMsg::MessageBuilder::buildMessage(*can_vect);
    fstream can_out(can_output, ios::out | ios::trunc | ios::binary);
    if (!can_msg->SerializeToOstream(&can_out)) {
        cerr << "Failed to write msg" << endl;
		return -1;
    }

	auto mtn_msg = ProtoMsg::MessageBuilder::buildMessage(hyps_hist, hypI.getIdealCells());
	fstream mtn_out(mtn_output, ios::out | ios::trunc | ios::binary);
	if (!mtn_msg->SerializeToOstream(&mtn_out)) {
		cerr << "Failed to write msg" << endl;
		return -1;
	}
        
    return 0;
}

