#include "MultiThread.h"

namespace RunMode {

	MultiThread::MultiThread(Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward)
	:Executor(map, forward, backward) {
	}


	MultiThread::~MultiThread() {
	}

	void MultiThread::run(std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his, const std::vector<Model::Detection> & dect_vec) {
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

	void MultiThread::autoDrive(std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info) {

	}

}
