//
//  BackwardChecking.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "BackwardChecking.h"
#include "../forward/UpdateByCell.h"
#include "../model/Map3D.h"
#include "../math/Gamma.h"
#include "../math/GaussianBlur.h"

namespace Backward {
    const double gamma_scale = 1.0;
	const size_t step = 4;
    
    using namespace std;
    using namespace Model;
    using namespace Forward;
    
    BackwardChecking::BackwardChecking()
        :forward_(new UpdateByCell()) {
        
    }
    
    BackwardChecking::~BackwardChecking() {
        
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
    double BackwardChecking::calcGaussianBlurMean(const Coordinate & location, const Cells & methane_cells, const Map3D & map) const {
		auto newCells = Math::GaussianBlur::BlurCells(map, location, methane_cells, step);
		auto locate_cell = newCells->getCell(location);
		if (locate_cell) {
			return locate_cell->getMethane().getMethane();
		}

		return Methane::getBackground();
    }
    
    //************************************
    // Method:    calcLikehood : calculate the gamma distribution like hood
    // FullName:  Backward::BackwardChecking::calcLikehood
    // Access:    protected 
    // Returns:   double
    // Qualifier: const
    // Parameter: const Hypothesis & hyp
    // Parameter: const Coordinate & detected_location
    // Parameter: double detected_concentration
    // Parameter: const Map3D & map
    //************************************
    double BackwardChecking::calcLikehood(const Hypothesis & hyp, const Coordinate & detected_location, double detected_concentration, const Map3D & map) const {
        auto mean = calcGaussianBlurMean(detected_location, *hyp.getMethaneCells(), map);
        return Math::Gamma::calcGammaPdf(mean, gamma_scale, detected_concentration);
    }
    
    //************************************
    // Method:    normalize : normalize the probability for all hypothesizes, make them sum to 1.
    // FullName:  Backward::BackwardChecking::normalize
    // Access:    protected 
    // Returns:   void
    // Qualifier: const
    // Parameter: vector<Hypothesis> & hyps
    //************************************
    void BackwardChecking::normalize(vector<Hypothesis> &hyps) const{
        auto sum = accumulate(hyps.begin(), hyps.end(), 0.0f, [](double sum, const Hypothesis & hyp){ return sum += hyp.getProbability();});
        for_each(hyps.begin(), hyps.end(), [sum](Hypothesis & hyp){hyp.setProbability(hyp.getProbability() / sum);});
    }
    
    //************************************
    // Method:    updateHypotheses : detect methane and update hypothesis.
    // FullName:  Backward::BackwardChecking::updateHypotheses    // Access:    public 
    // Returns:   shared_ptr<vector<Hypothesis>> : new hypothesis
    // Qualifier: const
    // Parameter: const vector<Hypothesis> & hyps : old hypothesis
    // Parameter: const Map3D & map 
    // Parameter: size_t time_count : how many iterations for forward model algorithm to carry.
    // Parameter: const vector<Leak> & detections
    //************************************
    shared_ptr<vector<Hypothesis>> BackwardChecking::updateHypotheses(const vector<Hypothesis> & hyps, const Map3D & map, size_t time_count, const vector<Leak> & detections) const {
        auto new_hyps = forward_->UpdateMethane(hyps, map, time_count);
        
        for (auto hyp : *new_hyps) {
            double likeHood = 1.0f;
            for (auto detection : detections) {
                likeHood *= calcLikehood(hyp, detection.location_, detection.concentration_, map);
            }
            hyp.setProbability(hyp.getProbability() * likeHood);
        }
        
        normalize(*new_hyps);
        
        return new_hyps;
    }
    
    
}