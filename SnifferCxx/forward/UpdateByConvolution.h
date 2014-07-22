#pragma once
#include "ForwardChecking.h"

namespace Forward {

	class UpdateByConvolution :	public ForwardChecking {
	public:
		UpdateByConvolution();
		virtual ~UpdateByConvolution();

		std::shared_ptr<Model::Cells> Deduce(const Model::Hypothesis & hypothesis, const Model::Map3D & map, size_t count) const;
	};

}

