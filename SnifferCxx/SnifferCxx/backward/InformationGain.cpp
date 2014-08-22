//
//  InformationGain.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 8/5/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//


#include "InformationGain.h"
#include "../model/Hypothesis.h"
#include "../model/Coordinate.h"
#include "../forward/ForwardChecking.h"
#include "../math/Gamma.h"
#include "BackwardChecking.h"
#include <numeric>

namespace Backward {
    using namespace std;
    using namespace Model;
    using namespace Forward;
    
    /**
     *  construct a information gain calculator
     *
     *  @param forward  reference of the forward checking algorithm
     *  @param backward reference of the backwrad checking algorithm
     *  @param map      reference of the map
     */
    InformationGain::InformationGain(const ForwardChecking & forward, const BackwardChecking & backward, const Map3D & map)
    :forward_(forward),
    backward_(backward),
    map_(map) {
        
    }
    
    
    InformationGain::~InformationGain() {
        
    }


    /**
     *  calculate entropy for one hypothesis
     *
     *  @param hyp a hypothesis as input
     *
     *  @return entropy value
     */
    entropy_t InformationGain::entropy(const vector<Hypothesis> & hyps) const{
		return accumulate(hyps.begin(), hyps.end(), 0.0, 
			[](double sum, const Hypothesis & it) { 
				return sum += -(it.getProbability() * log2(it.getProbability())); 
		});
    }
    
    
    /**
     *  calculate information gain by sum the entropy for all hypotheses together for one candidate
     *
     *  @param candidate one coordinate candidate for detection
     *  @param hyps      all virtual worlds represent all the hypotheses
     *
     *  @return expected information gain
     */
    entropy_t InformationGain::calcInforGain(const Coordinate & candidate, const vector<Hypothesis> & current_hyps, const vector<Hypothesis> & future_hyps) const{
        entropy_t ret_sum = 0.0;
        
        for (auto i=0; i < current_hyps.size(); i++) {
			auto assumed_futures = future_hyps;
			auto detection = backward_.calcGaussianBlurMean(candidate, *(assumed_futures[i].getMethaneCells()), map_);

			vector<double> probs;
			for (auto const & hyp : assumed_futures) {
				auto likehood = backward_.calcLikehood(hyp, candidate, detection, map_);
				probs.push_back(likehood * hyp.getProbability());
			}
			backward_.normalize(assumed_futures, probs);

            ret_sum += (entropy(current_hyps) - entropy(assumed_futures)) * current_hyps[i].getProbability();
        }
        
        return ret_sum;
    }
    
    
    /**
     *  calculate information gain for all the candidates
     *
     *  @param candidates all candidates detection
     *  @param hyps       all virtual worlds represent all our hypotheses
     *
     *  @return a set of score maped to all candidates
     */
    vector<entropy_t> InformationGain::calcInforGains(const vector<Coordinate> & candidates, const vector<Hypothesis> & hyps, int time_count) const{
        auto copy_hyps = make_shared<vector<Hypothesis>>(hyps);
        auto future_hyps = forward_.UpdateMethane(*copy_hyps, map_, time_count);
        
        vector<entropy_t> ret_vec;
        
        for(auto const & coord : candidates) {
            ret_vec.push_back(calcInforGain(coord, hyps, *future_hyps));
        }
        
        return ret_vec;
    }
}