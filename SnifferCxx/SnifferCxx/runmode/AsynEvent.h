#pragma once
#include "Executor.h"

namespace RunMode {

	class AsynEvent :
		public Executor
	{
	public:
		AsynEvent(Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward);
		virtual ~AsynEvent();

		void run(std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his, const std::vector<Model::Detection> & dect_vec);
		void autoDrive(std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info);
	};

}

