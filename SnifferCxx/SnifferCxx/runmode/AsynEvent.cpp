#include "AsynEvent.h"
#include "../forward/ForwardChecking.h"
#include "../backward/BackwardChecking.h"
#include "../model/Map3D.h"
#include "../model/Candidate.h"
#include "../model/Hypotheses.h"
#include <boost/bind.hpp>

namespace RunMode {
	using namespace std;

	AsynEvent::AsynEvent(const Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward)
		:Executor(map, forward, backward),
		dect_timer_(io_service_) {
	}


	AsynEvent::~AsynEvent()
	{
	}

	void AsynEvent::run(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, const std::vector<Model::Detection> & dect_vec) {
		if (dect_vec.size() <= 0) {
			return;
		}

		auto dect = dect_vec.begin();
		auto wind = dect->wv_;
		if (wind) {
			map_.updateWind(*wind);
		}

		io_service_.post(boost::bind(&AsynEvent::handle_Deduce, this, std::ref(*hyps_his.back())));

		dect_timer_.expires_from_now(boost::posix_time::milliseconds(dect->time_));
		dect_timer_.async_wait(boost::bind(&AsynEvent::handle_Detection, this, std::ref(hyps_his), dect, std::ref(dect_vec), boost::asio::placeholders::error));

		io_service_.run();
	}

	void AsynEvent::handle_Deduce(Model::Hypotheses & hyps) {
		if (hyps.getAsynFlag()) {
			forward_.update_once(hyps, map_);
			io_service_.post(boost::bind(&AsynEvent::handle_Deduce, this, std::ref(hyps)));
		}
	}

	void AsynEvent::handle_Detection(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, std::vector<Model::Detection>::const_iterator dect, const std::vector<Model::Detection> & dect_vec, const boost::system::error_code& error) {
		if (!error)
		{
			auto cur_hyps = hyps_his.back();
			cur_hyps->setAsynFlag(false);

			auto new_hyps = std::make_shared<Model::Hypotheses>();
			std::for_each(cur_hyps->begin(), cur_hyps->end(), [&new_hyps](Model::Hypothesis & hyp){new_hyps->push_back(Model::Hypothesis(hyp.getLeaks(), hyp.getProbability(), hyp.popMethaneCells())); });
			new_hyps = backward_.updateHypotheses(*new_hyps, map_, dect->detected_);
			hyps_his.push_back(new_hyps);

			if ((dect = std::next(dect, 1)) != dect_vec.end()) {
				auto wind = dect->wv_;
				if (wind) {
					map_.updateWind(*wind);
				}

				io_service_.post(boost::bind(&AsynEvent::handle_Deduce, this, std::ref(*hyps_his.back())));

				dect_timer_.expires_from_now(boost::posix_time::milliseconds(dect->time_));
				dect_timer_.async_wait(boost::bind(&AsynEvent::handle_Detection, this, std::ref(hyps_his), dect, std::ref(dect_vec), boost::asio::placeholders::error));
			}
		}
	}
}
