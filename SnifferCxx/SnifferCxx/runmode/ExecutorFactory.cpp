#include "ExecutorFactory.h"
#include "../runmode/AsynEvent.h"
#include "../runmode/MultiThread.h"
#include "../runmode/Executor.h"

namespace RunMode
{
	using namespace std;
	using namespace RunMode;

	ExecutorFactory::ExecutorFactory()
	{
	}


	ExecutorFactory::~ExecutorFactory()
	{
	}

	shared_ptr<Executor> ExecutorFactory::createExecutor(execute_mode run_type, const Model::Map3D& map, const Forward::ForwardChecking& forward, const Backward::BackwardChecking& backward)
	{
		switch (run_type)
		{
		case single:
			return make_shared<Executor>(map, forward, backward);

		case asyn_event:
			return make_shared<AsynEvent>(map, forward, backward);

		case multi_thread:
			return make_shared<MultiThread>(map, forward, backward);

		default:
			return nullptr;
		}
	}
}