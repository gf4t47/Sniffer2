//
//  main.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <thread>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "support/MyLog.h"

//init
#include "initializer/HypothesisInitializer.h"
#include "initializer/MapBuilder.h"
#include "initializer/DetectionInitializer.h"

//calc
#include "runmode/ExecutorFactory.h"
#include "runmode/Executor.h"
#include "model/Candidate.h"
#include "forward/ForwardChecking.h"

//message
#include "protomsg/ProtoMessageBuilder.h"
#include "directmsg/DirectMessageBuilder.h"
#include "model/Map3D.h"

#include "model/Coordinate.h"

using namespace std;
using namespace Initializer;
using namespace Model;

int main(int argc, const char * argv[])
{
	using namespace Forward;
	using namespace Backward;
	using namespace RunMode;
	using namespace Support;

	if (argc < 8) {
		cerr << argv[0] << " Missing some argument to indicate input/output files" << endl;
		return -1;
	}

	string map_cfg = argv[1];
	string hyps_cfg = argv[2];
	string dect_cfg = argv[3];
	string mtn_output = argv[4];
	string map_output = argv[5];
	string dect_output = argv[6];
	string can_output = argv[7];

	//init log
	Support::MyLog::init_log("../../bridge/output/Sniffer");

	//load map
	MapBuilder mb(map_cfg);
	auto map = mb.build();

	//load hypotheses
	HypothesisInitializer hypI(hyps_cfg);
	auto backward = hypI.getBackwardAlg();
	auto forward = hypI.getForwardAlg();
	auto hyps = hypI.getHyptheses();

	//load detection
	DetectionInitializer dectI(dect_cfg, *map, forward->getIterationPerSecond());
	auto init_vec = dectI.getInitSteadyStage();
	auto dect_vec = dectI.getDetections();
	auto auto_movement = dectI.getAutoMovementInfo();
	auto can_vect = make_shared<vector<Model::Detection>>();

	//calculation
	auto hyps_hist = make_shared<vector<shared_ptr<Hypotheses>>>();
	hyps_hist->push_back(hyps);
	auto executor = ExecutorFactory::createExecutor(dectI.getExecutorMode(), *map, *forward, *backward);
	executor->run(*hyps_hist, *dect_vec, init_vec);
	if (auto_movement) {
		executor->autoDrive(*hyps_hist, *dect_vec, *auto_movement);
	}
	else {
		can_vect->push_back(executor->nextStep(*hyps_hist, *dect_vec, AutoMovement(20, 8)));
	}

	//message output
//	ProtoMsg::ProtoMessageBuilder msg_builder(make_pair(mtn_output, hyps_hist), make_pair(dect_output, dect_vec), make_pair(can_output, can_vect), make_pair(map_output, map));
	DirectMsg::DirectMessageBuilder msg_builder(make_pair(mtn_output, hyps_hist), make_pair(dect_output, dect_vec), make_pair(can_output, can_vect), make_pair(map_output, map));
	msg_builder.WriteMsg(hypI.getIdealCells(), hypI.getDetectionOnly());

	return 0;
}

