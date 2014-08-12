//
//  main.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <thread>
#include <fstream>
#include "initializer/HypothesisInitializer.h"
#include "initializer/MapBuilder.h"
#include "initializer/DetectionInitializer.h"
#include "backwrad/BackwardChecking.h"
#include "forward/ForwardChecking.h"
#include "filesystem/MessageBuilder.h"
#include "filesystem/hypothesis.pb.h"
#include "filesystem/dect.pb.h"

using namespace std;
using namespace Model;

int main(int argc, const char * argv[])
{
	using namespace initializer;
	using namespace Forward;
    
    if (argc < 7) {
        cerr << argv[0] << " Missing some argument to indicate input files" << endl;
        return -1;
    }
    
    string map_cfg = argv[1];
    string hyps_cfg = argv[2];
    string dect_cfg = argv[3];
    string mtn_output = argv[4];
    string map_output = argv[5];
    string dect_output = argv[6];

    //load map
    MapBuilder mb(map_cfg);
    auto map = mb.build();
    
    //load hypotheses
    HypothesisInitializer hypI(hyps_cfg);
    auto backward = hypI.getBackwardAlg();
	auto forward = hypI.getForwardAlg();
    auto hyps = hypI.getHyptheses();
    
    //load detection
	shared_ptr<vector<detection>> dect_vect;
	bool multiple_thread;
    tie(dect_vect, multiple_thread) = DetectionInitializer::load(dect_cfg);

    //calculation
    vector<shared_ptr<vector<Hypothesis>>> hyps_hist;
    hyps_hist.push_back(hyps);
    if (!multiple_thread) {
        for (auto dect : *dect_vect)
        {
            hyps = backward->updateHypotheses(*hyps, *map, dect.detected_, dect.time_, forward);
            hyps_hist.push_back(hyps);
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
    fstream map_out(map_output, ios::out | ios::trunc | ios::binary);
    if (!map_msg->SerializeToOstream(&map_out)) {
        cerr << "Failed to write msg" << endl;
		return -1;
    }
    
    auto dect_msg = Filesystem::MessageBuilder::buildMessage(*dect_vect);
    fstream dect_out(dect_output, ios::out | ios::trunc | ios::binary);
    if (!dect_msg->SerializeToOstream(&dect_out)) {
        cerr << "Failed to write msg" << endl;
		return -1;
    }

	auto mtn_msg = Filesystem::MessageBuilder::buildMessage(hyps_hist, hypI.getIdealCells());
	fstream mtn_out(mtn_output, ios::out | ios::trunc | ios::binary);
	if (!mtn_msg->SerializeToOstream(&mtn_out)) {
		cerr << "Failed to write msg" << endl;
		return -1;
	}
        
    return 0;
}

