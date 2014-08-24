#include "AsynEvent.h"

namespace RunMode {

	AsynEvent::AsynEvent(Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward)
		:Executor(map, forward, backward) {
	}


	AsynEvent::~AsynEvent()
	{
	}

	void AsynEvent::run(std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his, const std::vector<Model::Detection> & dect_vec) {

	}

	void AsynEvent::autoDrive(std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info) {

	}

}
