#include "ExecutorFactory.h"
#include "../runmode/AsynEvent.h"
#include "../runmode/MultiThread.h"
#include "../runmode/SingleForward.h"

namespace RunMode {
	using namespace std;
	using namespace RunMode;

	ExecutorFactory::ExecutorFactory()
	{
	}


	ExecutorFactory::~ExecutorFactory()
	{
	}

	shared_ptr<Executor> ExecutorFactory::createExecutor(execute_mode run_type, Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward) {
		switch (run_type) {
		case single:
			return make_shared<SingleForward>(map, forward, backward);
			break;

		case asyn_event:
			return make_shared<AsynEvent>(map, forward, backward);
			break;

		case multi_thread:
			return make_shared<MultiThread>(map, forward, backward);
			break;

		default:
			return nullptr;
			break;
		}
	}
}
