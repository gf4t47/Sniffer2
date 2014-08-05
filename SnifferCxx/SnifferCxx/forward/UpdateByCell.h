//
//  UpdateByCell.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__UpdateByCell__
#define __SnifferCxx__UpdateByCell__

#include "ForwardChecking.h"
#include <unordered_map>
#include "../model/Cells.h"
#include "../model/Map3D.h"

namespace Forward {

	typedef std::unordered_map<Model::Coordinate, size_t, Model::CoordHasher> pos_conc_t;

	class UpdateByCell : public ForwardChecking {
	public:
        UpdateByCell(range_t kernel_range);
		~UpdateByCell();

	protected:
        virtual std::shared_ptr<Model::Cells> calcEnds(const Model::Cell & cell, const Model::Map3D & map) const;
		virtual std::shared_ptr<Model::Cells> calcEnds(const Model::Cells & cells, const Model::Map3D & map) const; 
        std::shared_ptr<Model::Cell> calcEndcell(const Model::Coordinate & statPos, const Model::Coordinate & endPos, const Model::Map3D & map, bool checkFullPath = true) const;

	private:
		std::shared_ptr<pos_conc_t> calcGaussianEnds(const Model::Coordinate & startPos, const Model::WindVector & wv, const Model::mtn_t particle_num, const Model::Map3D & map) const;

	};
}

#endif /* defined(__SnifferCxx__UpdateByCell__) */
