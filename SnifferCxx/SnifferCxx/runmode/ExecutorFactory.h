#pragma once
#include <memory>

namespace Model
{
	class Map3D;
}

namespace Forward
{
	class ForwardChecking;
}

namespace Backward
{
	class BackwardChecking;
}

namespace RunMode
{
	class Executor;

	enum execute_mode
	{
		single,
		multi_thread,
		asyn_event
	};

	class ExecutorFactory
	{
	public:
		ExecutorFactory();
		~ExecutorFactory();

		static std::shared_ptr<Executor> createExecutor(execute_mode run_type, const Model::Map3D& map, const Forward::ForwardChecking& forward, const Backward::BackwardChecking& backward);
	};
}