#pragma once
#include "Executor.h"

namespace RunMode
{
	class MultiThread :
		public Executor
	{
	public:
		MultiThread(const Model::Map3D& map, const Forward::ForwardChecking& forward, const Backward::BackwardChecking& backward);
		virtual ~MultiThread();

		void run(std::vector<std::shared_ptr<Model::Hypotheses>>& hyps_his, const std::vector<Model::Detection>& dect_vec);
	};
}