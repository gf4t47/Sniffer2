//
//  ForwardChecking.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "ForwardChecking.h"
#include "../model/Hypothesis.h"
#include "../model/Cells.h"
#include "../model/Map3D.h"

namespace Forward {
    using namespace std;
    using namespace Model;
    
    ForwardChecking::ForwardChecking() {
        
    }
    
	ForwardChecking::~ForwardChecking() {

	}
   
    //************************************
	// Method:    Deduce : enter face for this algorithm class
	// FullName:  Forward::ForwardChecking::Deduce
	// Access:    public
	// Returns:   shared_ptr<Cells>
	// Qualifier: const
	// Parameter: const Hypothesis & hypothesis
	// Parameter: const Map3D & map
	// Parameter: size_t count
	//************************************
	shared_ptr<Cells> ForwardChecking::Deduce(Hypothesis & hypothesis, const Map3D & map, size_t count) const {
        
		Cells leakCells; // more leaked methane cells added in each iteration.
		for (auto leak : hypothesis.getLeaks()) {
			auto leakCell = map.getCell(leak.location_);
			leakCell.setMethaneConcentration(leak.concentration_);
			leakCells.updateCell(leakCell);
		}
        
        auto methane_cells = hypothesis.getMethaneCells();
        auto ret_cells = make_shared<Cells>();
        if (methane_cells) {
            ret_cells = make_shared<Cells>(*hypothesis.getMethaneCells()); //copy construtor here to storage the history of a hypothesis.
        }
        
		for (size_t i = 0; i < count; i++) {
			ret_cells->mergeCellsByAddMethane(leakCells);
			ret_cells = calcEnds(*ret_cells, map);
            hypothesis.addCellsHistory(ret_cells);
		}
        
        return ret_cells;
	}
    
    shared_ptr<vector<Hypothesis>> ForwardChecking::UpdateMethane(vector<Hypothesis> & hyps, const Map3D & map, size_t count) const {
        auto ret_hyps = make_shared<vector<Hypothesis>>();
        
        for (auto & hyp : hyps) {
            auto newCells = Deduce(hyp, map, count);
            Hypothesis newHyp(hyp.getLeaks(), hyp.getProbability(), newCells);
			ret_hyps->push_back(newHyp);
        }
        
        return ret_hyps;
    }

	void ForwardChecking::operator()(const std::vector<Model::Hypothesis> & hyps) {

	}
}