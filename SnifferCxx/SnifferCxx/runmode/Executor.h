#pragma once

#include <vector>
#include <memory>

namespace Model {
	class Map3D;
	class Hypothesis;
	class Hypotheses;

	struct Detection;
	struct AutoMovement;
}

namespace Forward {
	class ForwardChecking;
}

namespace Backward {
	class BackwardChecking;
}

namespace RunMode {
	class Executor {
	public:
		Executor(Model::Map3D & map, const Forward::ForwardChecking & forward, const Backward::BackwardChecking & backward);
		virtual ~Executor();

		virtual void run(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, const std::vector<Model::Detection> & dect_vec) = 0;
		virtual void autoDrive(std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, std::vector<Model::Detection> & dect_vec, const Model::AutoMovement & auto_info) = 0;

	protected:
		Model::Map3D & map_;
		const Forward::ForwardChecking & forward_;
		const Backward::BackwardChecking & backward_;
	};
}


