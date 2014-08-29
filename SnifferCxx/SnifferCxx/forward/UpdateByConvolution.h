#pragma once
#include "UpdateByCell.h"

namespace Forward {

	class UpdateByConvolution :	public UpdateByCell {
	public:
		UpdateByConvolution(range_t kernel_range, int iteration_per_sec);
		virtual ~UpdateByConvolution();
       
    protected:
        virtual std::shared_ptr<Model::Cells> calcEnds(const Model::Cell & cell, const Model::Map3D & map) const;
	};

}

