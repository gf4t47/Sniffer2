//
//  ForwardChecking.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "ForwardChecking.h"
#include "../model/Hypothesis.h"
#include "../math/GaussianBlur.h"
#include "../model/Cells.h"

namespace Forward {
    using namespace std;
    using namespace Model;
    
    ForwardChecking::ForwardChecking(int blur_range)
        :blur_range_(blur_range) {
        
    }
    
	ForwardChecking::~ForwardChecking() {

	}
    
    int ForwardChecking::getBlurRange() const{
        return blur_range_;
    }
    
    shared_ptr<vector<Hypothesis>> ForwardChecking::UpdateMethane(const vector<Hypothesis> & hyps, const Map3D & map, size_t count) const {
        auto ret_hyps = make_shared<vector<Hypothesis>>();
        
        for (auto hyp : hyps) {
            auto newCells = Deduce(hyp, map, count);
            Hypothesis newHyp(hyp.getLeaks(), hyp.getProbability(), newCells);
            ret_hyps->push_back(newHyp);
        }
        
        return ret_hyps;
    }

	//************************************
	// Method:    calcGaussianBlurMean : use Gaussian convolution to blur the methane before output as the gamma distribution mean parameter.
	// FullName:  Backward::BackwardChecking::calcGaussianBlurMean
	// Access:    protected 
	// Returns:   double
	// Qualifier: const
	// Parameter: const Coordinate & location
	// Parameter: const Cells & methane_cells
	// Parameter: const Map3D & map
	//************************************
	double ForwardChecking::calcGaussianBlurMean(const Coordinate & location, const Cells & methane_cells, const Map3D & map) const {
		auto newCells = Math::GaussianBlur::blurCells(location, getBlurRange(), methane_cells, map);
		auto locate_cell = newCells->getCell(location);
		if (locate_cell) {
			return locate_cell->getMethane().getMethane();
		}

		return Methane::getBackground();
	}
}