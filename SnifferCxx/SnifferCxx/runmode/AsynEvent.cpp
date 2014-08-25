#include "AsynEvent.h"
#include "../forward/ForwardChecking.h"
#include "../backward/BackwardChecking.h"
#include "../model/Map3D.h"
#include "../model/Candidate.h"
#include "../model/Hypotheses.h"
#include <boost/bind.hpp>

namespace RunMode {
	using namespace std;

	AsynEvent::AsynEvent(Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward)
		:Executor(map, forward, backward),
		dect_timer_(io_service_) {
	}


	AsynEvent::~AsynEvent()
	{
	}

	void AsynEvent::run(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, const std::vector<Model::Detection> & dect_vec) {
		io_service_.post(boost::bind(&AsynEvent::handle_Deduce, this, *hyps_his.back()));
	}

	void AsynEvent::autoDrive(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info) {

	}

	void AsynEvent::handle_Deduce(Model::Hypotheses & hyps) {
		//forward_.UpdateMethane(hyps, map_, 1);
		//io_service_.post(boost::bind(&AsynEvent::handle_Deduce, this, *hyps_his.back()));
	}

	void AsynEvent::handle_Detection(Model::Hypotheses & hyps, const Model::Detection & dect) {
		if (dect.wv_) {
			map_.updateWind(*dect.wv_);
		}

		backward_.updateHypotheses(hyps, map_, dect.detected_);
	}
}
