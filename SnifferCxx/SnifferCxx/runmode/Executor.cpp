#include "Executor.h"

namespace RunMode {
	Executor::Executor(Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward) 
	:map_(map), 
	forward_(forward),
	backward_(backward) {

	}


	Executor::~Executor() {
	}
}

