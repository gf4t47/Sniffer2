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
    using namespace std;
    using namespace Model;
    using namespace Forward;
    
    BackwardChecking::BackwardChecking(range_t blur_range, range_t kernel_range)
        :blur_range_(blur_range),
        kernel_range_(kernel_range) {
        
    }
    
    BackwardChecking::~BackwardChecking() {
        
    }

	range_t BackwardChecking::getBlurRange() const{
		return blur_range_;
	}
    
    range_t BackwardChecking::getKernelRange() const {
        return kernel_range_;
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
		auto newCells = Math::GaussianBlur::blurCells(location, getBlurRange(), methane_cells, map, getKernelRange());
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
        return Math::Gamma::calcGammaPdf(detected_concentration, mean);
    }
    
    //************************************
    // Method:    normalize : normalize the probability for all hypothesizes, make them sum to 1.
    // FullName:  Backward::BackwardChecking::normalize
    // Access:    protected 
    // Returns:   void
    // Qualifier: const
    // Parameter: vector<Hypothesis> & hyps
    //************************************
    void BackwardChecking::normalize(vector<Hypothesis> & hyps, const vector<double> & hyps_probability) const{
        auto sum = accumulate(hyps_probability.begin(), hyps_probability.end(), 0.0, [](double sum, const double pro){ return sum += pro;});
        for(auto i = 0; i < hyps.size(); i++) {
            hyps[i].setProbability(hyps_probability[i] / sum);
        }
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
    shared_ptr<vector<Hypothesis>> BackwardChecking::updateHypotheses(vector<Hypothesis> & hyps, const Map3D & map, const vector<Leak> & detections, size_t time_count, const shared_ptr<ForwardChecking> forward) const {
        auto ret_hyps = make_shared<vector<Hypothesis>>(hyps);
        if(forward) {
            ret_hyps = forward->UpdateMethane(hyps, map, time_count);
        }
        
        vector<double> hyps_probability;
        for (auto const & hyp : *ret_hyps) {
            double likeHood = 1.0;
            for (auto detection : detections) {
                likeHood *= calcLikehood(hyp, detection.location_, detection.concentration_, map);
            }
            
            hyps_probability.push_back(hyp.getProbability() * likeHood);
        }
        
        normalize(*ret_hyps, hyps_probability);
        
        return ret_hyps;
    }
    
    
}