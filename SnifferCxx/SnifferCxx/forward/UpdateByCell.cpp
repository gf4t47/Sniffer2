//
//  UpdateByCell.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "UpdateByCell.h"
#include "../model/Hypothesis.h"
#include "../math/Gaussian.h"
#include <math.h>

namespace Forward {
	using namespace std;
	using namespace Model;
    
    UpdateByCell::UpdateByCell(range_t kernel_range)
    :ForwardChecking(kernel_range) {
        
    }

	UpdateByCell::~UpdateByCell() {

	}

	//************************************
	// Method:    calcGaussianEnds : calculate ideal end positions for particles in one cell(located in startPos), no collision influence yet.
	// FullName:  Forward::UpdateByCell::calcGaussianEnds
	// Access:    private 
	// Returns:   shared_ptr<pos_val_st> : a list of random end positions with their methane concentrations
	// Qualifier: const
	// Parameter: const Coordinate & startPos 
	// Parameter: const WindVector & wv
	// Parameter: const mtn_t particle_num : methane concentration in the start cell
	// Parameter: const Map3D & map
	//************************************
	shared_ptr<pos_conc_t> UpdateByCell::calcGaussianEnds(const Coordinate & startPos, const WindVector & wv, const mtn_t particle_num, const Map3D & map) const {
		auto winds = Math::Gaussian::RandomWindVectors(wv, getKernelRange() * map.getUnit(), ceil(particle_num));
		auto particle_num_per_wind = 1;

		auto map_ret = make_shared<pos_conc_t>(); //a hash table used to merge the methane particles move into same cell.
		for_each(winds->begin(), winds->end(),
			[&map_ret, particle_num_per_wind, &startPos, &map](const WindVector & wv) {
			auto endPos = map.calcPosition(startPos, wv);
			auto find_ret = map_ret->find(endPos);
			if (find_ret == map_ret->end()) {
				(*map_ret)[endPos] = particle_num_per_wind;
			}
			else {
				(*map_ret)[endPos] += particle_num_per_wind;
			}
		});

		return map_ret;
	}

	//************************************
	// Method:    calcEndcell : caculate real end cell by start position and ideal end position, collision affected the result by calling Map3D::calcCollisionByEndCell or calcCollisionByFullPath
	// FullName:  Forward::UpdateByCell::calcEndcell
	// Access:    private 
	// Returns:   shared_ptr<Cell>
	// Qualifier: const
	// Parameter: const Coordinate & statPos
	// Parameter: const Coordinate & endPos
	// Parameter: const Map3D & map
	//************************************
	shared_ptr<Cell> UpdateByCell::calcEndcell(const Coordinate & statPos, const Coordinate & endPos, const Map3D & map, bool checkFullPath /* = false*/) const {
		if (checkFullPath)
		{
			return map.calcCollisionByFullPath(statPos, endPos);
		}

		return map.calcCollisionByEndCell(statPos, endPos);
	}

	//************************************
	// Method:    calcEnds : calculate the methane distribution started from one cell to multiple cells
	// FullName:  Forward::UpdateByCell::calcEnds
	// Access:    protected 
	// Returns:   shared_ptr<Cells> : all the cells has methane after distribution
	// Qualifier: const
	// Parameter: const Cell & cell : methane start cell
	// Parameter: const Map3D & map
	//************************************
	shared_ptr<Cells> UpdateByCell::calcEnds(const Cell & cell, const Map3D & map) const {
		if (!cell.hasMethane()) {
			return make_shared<Cells>();
		}

		auto curPos = cell.getCoordinate();
		auto end_vals = calcGaussianEnds(curPos, cell.getWind().getCalcWind(), cell.getMethane().getParticleNum(), map);

		auto new_cells = make_shared<Cells>();
		for (auto entry : *end_vals) {
			auto endCell = calcEndcell(curPos, entry.first, map);
			if (endCell) {
				auto endCoord = endCell->getCoordinate();
				auto same_position_cell = new_cells->getCell(endCoord);
				mtn_t original_methane = 0;
				if (same_position_cell) {
					original_methane = same_position_cell->getMethane().getParticleNum();
				}

				endCell->setMethaneConcentration(original_methane + entry.second);
				new_cells->updateCell(*endCell);
			}
		}

		return new_cells;
	}

	//************************************
	// Method:    calcEnds : calculate the methane distribution started from multiple cells, and re sample
	// FullName:  Forward::UpdateByCell::calcEnds
	// Access:    protected 
	// Returns:   shared_ptr<Cells> : all the cells have methane after distribution and re sampling.
	// Qualifier: const
	// Parameter: const Model::Cells & cells
	// Parameter: const Model::Map3D & map
	//************************************
	shared_ptr<Cells> UpdateByCell::calcEnds(const Model::Cells & cells, const Model::Map3D & map) const {
		auto ret_cells = make_shared<Cells>();
		for (auto entry : cells) {
			auto new_cells = calcEnds(entry.second, map);
			ret_cells->mergeCellsByAddMethane(*new_cells);
		}

//        cout <<"intput cells = "<<cells.size()<<" output cells = " << ret_cells->size() << endl;
		return ret_cells;
	}
}