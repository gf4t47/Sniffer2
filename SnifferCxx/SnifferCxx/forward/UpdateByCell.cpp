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
#include "../model/Cells.h"
#include "../model/Map3D.h"
#include <math.h>

namespace Forward {
	using namespace std;
	using namespace Model;
    
    UpdateByCell::UpdateByCell(range_t kernel_range, int iteration_per_sec)
    :ForwardChecking(kernel_range, iteration_per_sec) {
        
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
	shared_ptr<pos_conc_t> UpdateByCell::calcGaussianEnds(const Cell & start_cell, const Map3D & map) const {
		auto wv_per_iteration = start_cell.getWind().getCalcWind() * (1.0 / (double)getIterationPerSecond());
		auto winds = Math::Gaussian::RandomWindVectors(wv_per_iteration, getKernelRange() * map.getUnit(), ceil(start_cell.getMethane().getConcentration()));
		auto concentration_per_wind = 1;

		auto map_ret = make_shared<pos_conc_t>(); //a hash table used to merge the methane particles move into same cell.
		for (auto const & wv : *winds) {
			Coordinate position;
			WindVector potential;

			tie(position, potential) = map.calcPosition(start_cell.getCoordinate(), wv + start_cell.getMethane().getPotential());
			auto find_ret = map_ret->find(position);
			if (find_ret == map_ret->end()) {
				(*map_ret)[position] = Methane(concentration_per_wind, potential);
			}
			else {
				(*map_ret)[position] = Methane(concentration_per_wind, potential) + (*map_ret)[position];
			}
		}

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
	shared_ptr<Cell> UpdateByCell::calcEndcell(const Coordinate & statPos, const Coordinate & endPos, const Map3D & map, bool checkFullPath /* = true*/) const {
		shared_ptr<Cell> ret;

		if (checkFullPath) {
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

		auto end_vals = calcGaussianEnds(cell, map);

		auto new_cells = make_shared<Cells>();
		for (auto entry : *end_vals) {
			auto endCell = calcEndcell(cell.getCoordinate(), entry.first, map);
			if (endCell) {
				auto same_position_cell = new_cells->getCell(endCell->getCoordinate());
				if (same_position_cell) {
					endCell->setMethane(same_position_cell->getMethane() + entry.second);
				}
				else {
					endCell->setMethane(entry.second);
				}

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

        //cout <<"intput cells = "<<cells.size()<<" output cells = " << ret_cells->size() << endl;
		return ret_cells;
	}
}