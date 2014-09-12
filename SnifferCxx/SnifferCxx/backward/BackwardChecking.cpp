//
//  BackwardChecking.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "BackwardChecking.h"
#include "../forward/UpdateByCell.h"
#include "../model/Hypotheses.h"
#include "../model/Map3D.h"
#include "../math/Gamma.h"
#include "../math/GaussianBlur.h"
#include "../model/Cells.h"
#include "../model/Candidate.h"
#include "../support/MyLog.h"

namespace Backward {
	using namespace Support;
    using namespace std;
    using namespace Model;
    using namespace Forward;

	const double gamma_background_probability = 0.00001;

//	unique_ptr<MyLog> BackwardChecking::lg_(make_unique<MyLog>());
    unique_ptr<MyLog> BackwardChecking::lg_(new MyLog());
    
    BackwardChecking::BackwardChecking(range_t gaussian_blur_range, range_t gaussian_kernel_range, range_t gamma_variance)
        :gaussian_blur_range_(gaussian_blur_range),
        gaussian_kernel_range_(gaussian_kernel_range),
		gamma_variance_(gamma_variance) {
        
    }
    
    BackwardChecking::~BackwardChecking() {
        
    }

	range_t BackwardChecking::getBlurRange() const{
		return gaussian_blur_range_;
	}
    
    range_t BackwardChecking::getKernelRange() const {
        return gaussian_kernel_range_;
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
	Model::mtn_t BackwardChecking::calcGaussianBlurMean(const Coordinate & location, const Cells & methane_cells, const Map3D & map) const {
		auto newCells = Math::GaussianBlur::blurCells(location, getBlurRange(), methane_cells, map, getKernelRange());
		auto locate_cell = newCells->getCell(location);
		auto background_partile = Methane::transConcentration2Particle(Methane::getBackgroundConcentration());
		if (locate_cell) {
			return locate_cell->getMethane().getParitcles() + background_partile;
		}

		return background_partile;
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
    double BackwardChecking::calcLikehood(const Hypothesis & hyp, const Coordinate & detected_location, double detected_particles, const Map3D & map) const {
        auto mean = calcGaussianBlurMean(detected_location, *hyp.getMethaneCells(), map); //unit : particle
        auto ret = Math::Gamma::calcGammaPdf(detected_particles, mean, gamma_variance_);  //where is this gamma_variance_ comes from? gamma fit the data by python -_-, sorry!
        
		BOOST_LOG_SEV(*lg_, severity_level::debug) << "calculated = " << detected_location << ": " << mean;
		BOOST_LOG_SEV(*lg_, severity_level::debug) << "detected   = " << detected_location << ": " << detected_particles;
        BOOST_LOG_SEV(*lg_, severity_level::debug) << "likehood = " << ret << " + " << gamma_background_probability;
        
		return ret + gamma_background_probability;
    }
    
    //************************************
    // Method:    normalize : normalize the probability for all hypothesizes, make them sum to 1.
    // FullName:  Backward::BackwardChecking::normalize
    // Access:    protected 
    // Returns:   void
    // Qualifier: const
    // Parameter: vector<Hypothesis> & hyps
    //************************************
    void BackwardChecking::normalize(Hypotheses & hyps, const vector<double> & hyps_probability) const{
        auto sum = accumulate(hyps_probability.begin(), hyps_probability.end(), 0.0, [](double sum, const double pro){ return sum += pro;});
        for(auto i = 0; i < hyps.size(); i++) {
            auto prob = hyps_probability[i] / sum;
            hyps[i].setProbability(prob);
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
    shared_ptr<Hypotheses> BackwardChecking::updateHypotheses(Hypotheses & hyps, const Map3D & map, const vector<Candidate> & detections) const {
        namespace logging = boost::log;
        namespace keywords = boost::log::keywords;
        namespace sinks = boost::log::sinks;
        
        auto ret_hyps = make_shared<Hypotheses>(hyps);
        
        vector<double> hyps_probability;
		size_t count = 0;
        for (auto const & hyp : *ret_hyps) {
            double likeHood = 1.0;

			//BOOST_LOG_SEV(*lg_, severity_level::debug) << "hypothesis" << count << " is updating: ";
            for (auto detection : detections) {
                if (map.insideMap(detection.location_)) {
					likeHood *= calcLikehood(hyp, detection.location_, Methane::transConcentration2Particle(detection.concentration_), map);
                }
            }
			//BOOST_LOG_SEV(*lg_, severity_level::debug) << "hypothesis" << count << " is finished.";

            hyps_probability.push_back(hyp.getProbability() * likeHood);

			count++;
        }
        
        normalize(*ret_hyps, hyps_probability);
        
        for (int i=0; i<ret_hyps->size(); i++) {
            BOOST_LOG_SEV(*lg_, severity_level::info) << "hypothesis"<<i<<"'s probability = " << (*ret_hyps)[i].getProbability();
        }
        
        return ret_hyps;
    }
    
    
}