#pragma once
#include "UpdateByCell.h"

namespace Forward {

	class UpdateByConvolution :	public UpdateByCell {
	public:
		UpdateByConvolution(int blur_range);
		virtual ~UpdateByConvolution();
        
        virtual std::shared_ptr<Model::Cells> calcEnds(const Model::Cell & cell, const Model::Map3D & map) const;
	};

}

