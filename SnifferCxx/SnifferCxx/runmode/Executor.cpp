#include "Executor.h"
#include "../backward/CandidateGenerator.h"
#include "../model/Candidate.h"
#include "../model/Map3D.h"
#include "../model/Hypotheses.h"
#include "../forward/ForwardChecking.h"
#include "../backward/BackwardChecking.h"

namespace RunMode {
	using namespace std;

	Executor::Executor(const Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward) 
	:map_(map), 
	forward_(forward),
	backward_(backward) {

	}


	Executor::~Executor() {
	}

	std::shared_ptr<Model::Hypotheses> Executor::run_one_dect(Model::Hypotheses & hyps, const Model::Detection & dect) const{
		if (dect.wv_) {
			map_.updateWind(*dect.wv_);
		}

		return backward_.updateHypotheses(*forward_.UpdateMethane(hyps, map_, dect.time_), map_, dect.detected_);
	}

	std::shared_ptr<Model::Hypotheses> Executor::init2steadystage(const Model::Hypotheses & hyps, const std::vector<Model::Detection> & init) const {
		auto curHyps = make_shared<Model::Hypotheses>(hyps);

		for (auto const & it : init) {
			if (it.wv_) {
				map_.updateWind(*it.wv_);
			}

			curHyps = forward_.initHypotheses(*curHyps, map_, it.time_);
		}

		return curHyps;
	}

	void Executor::run(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, const std::vector<Model::Detection> & dect_vec, const std::shared_ptr<std::vector<Model::Detection>> init) const {
		if (init) {
			hyps_his.push_back(init2steadystage(*hyps_his.back(), *init));
		}

		for (auto const & dect : dect_vec) {
			hyps_his.push_back(run_one_dect(*hyps_his.back(), dect));
		}
	}

	void Executor::autoDrive(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info) const {
		using namespace Backward;
		using namespace Model;

		CandidateGenerator cg(forward_, backward_, map_);
		while (hyps_his.back()->getMaxProbHyp().getProbability() < auto_info.threshold_) {
			auto max_can = cg.calcBestCandidate(dect_vec.back().detected_.back().location_, auto_info.time_, auto_info.distance_, *hyps_his.back());
			cout << "max candidate : " << max_can.location_ << " = " << max_can.concentration_ << endl;

			Detection next_dect;
			next_dect.time_ = auto_info.time_;
			next_dect.detected_.push_back(Candidate(max_can.location_, 2.0));
			dect_vec.push_back(next_dect);

			hyps_his.push_back(run_one_dect(*hyps_his.back(), next_dect));
		}
	}

	Model::Detection Executor::nextStep(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info) const {
		using namespace Backward;
		using namespace Model;

		CandidateGenerator cg(forward_, backward_, map_);
		auto can_vec = cg.calcCandidates(dect_vec.back().detected_.back().location_, auto_info.time_, auto_info.distance_, *hyps_his.back());
		Detection ret_dect;
		ret_dect.time_ = auto_info.time_;
		for (auto const & can : can_vec) {
			ret_dect.detected_.push_back(can);
		}

		return ret_dect;
	}
}

