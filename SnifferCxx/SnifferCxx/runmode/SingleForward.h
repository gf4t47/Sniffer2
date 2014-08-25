#pragma once
#include "Executor.h"

namespace RunMode {
	class SingleForward :
		public Executor
	{
	public:
		SingleForward(Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward);
		virtual ~SingleForward();

		void run(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, const std::vector<Model::Detection> & dect_vec);
		void autoDrive(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info);

	private:
		std::shared_ptr<Model::Hypotheses> run_once(Model::Hypotheses & hyps, const Model::Detection & dect);
	};
}

