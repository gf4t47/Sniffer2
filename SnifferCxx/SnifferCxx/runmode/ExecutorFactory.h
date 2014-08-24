#pragma once
#include <memory>
#include "Executor.h"

namespace RunMode {

	enum execute_mode {
		single,
		multi_thread,
		asyn_event
	};

	class ExecutorFactory
	{
	public:
		ExecutorFactory();
		~ExecutorFactory();

		static std::shared_ptr<Executor> createExecutor(execute_mode run_type, Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward);
	};

}

