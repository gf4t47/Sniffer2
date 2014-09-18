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

	void AsynEvent::run(vector<shared_ptr<Model::Hypotheses>> & hyps_his, const vector<Model::Detection> & dect_vec, const shared_ptr<vector<Model::Detection>> init) {
		if (dect_vec.size() <= 0) {
			return;
		}

		if (init) {
			hyps_his.push_back(init2steadystage(*hyps_his.back(), *init));
		}

		auto dect = dect_vec.begin();
		auto wind = dect->wv_;
		if (wind) {
			map_.updateWind(*wind);
		}

		io_service_.post(boost::bind(&AsynEvent::handle_Deduce, this, ref(*hyps_his.back())));

		dect_timer_.expires_from_now(boost::posix_time::milliseconds(dect->time_));
		dect_timer_.async_wait(bind(&AsynEvent::handle_Detection, this, ref(hyps_his), dect, ref(dect_vec), boost::asio::placeholders::error));

		io_service_.run();
	}

	void AsynEvent::handle_Deduce(Model::Hypotheses & hyps) {
		if (hyps.getAsynFlag()) {
			forward_.update_once(hyps, map_);
			io_service_.post(boost::bind(&AsynEvent::handle_Deduce, this, ref(hyps)));
		}
	}

	void AsynEvent::handle_Detection(vector<shared_ptr<Model::Hypotheses>> & hyps_his, vector<Model::Detection>::const_iterator dect, const vector<Model::Detection> & dect_vec, const boost::system::error_code& error) {
		if (!error)
		{
			auto cur_hyps = hyps_his.back();
			cur_hyps->setAsynFlag(false);

			auto new_hyps = make_shared<Model::Hypotheses>();
			for_each(cur_hyps->begin(), cur_hyps->end(), [&new_hyps](Model::Hypothesis & hyp){new_hyps->push_back(Model::Hypothesis(hyp.getLeaks(), hyp.getProbability(), hyp.popMethaneCells())); });
			new_hyps = backward_.updateHypotheses(*new_hyps, map_, dect->detected_);
			hyps_his.push_back(new_hyps);

			if ((dect = next(dect, 1)) != dect_vec.end()) {
				auto wind = dect->wv_;
				if (wind) {
					//auto wv = *wind;
					map_.updateWind(*wind);
				}

				io_service_.post(boost::bind(&AsynEvent::handle_Deduce, this, ref(*hyps_his.back())));

				dect_timer_.expires_from_now(boost::posix_time::milliseconds(dect->time_));
				dect_timer_.async_wait(bind(&AsynEvent::handle_Detection, this, ref(hyps_his), dect, ref(dect_vec), boost::asio::placeholders::error));
			}
		}
	}
}
