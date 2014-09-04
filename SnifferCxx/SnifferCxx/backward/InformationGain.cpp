//
//  InformationGain.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 8/5/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <numeric>
#include "InformationGain.h"
#include "../model/Hypotheses.h"
#include "../model/Coordinate.h"
#include "../forward/ForwardChecking.h"
#include "../math/Gamma.h"
#include "BackwardChecking.h"
#include "../support/MyLog.h"

namespace Backward {
    using namespace std;
    using namespace Model;
    using namespace Forward;
	using namespace Support;

	unique_ptr<MyLog> InformationGain::lg_(make_unique<MyLog>());
    
    /**
     *  construct a information gain calculator
     *
     *  @param forward  reference of the forward checking algorithm
     *  @param backward reference of the backward checking algorithm
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
    entropy_t InformationGain::entropy(const Hypotheses & hyps) const{
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
    entropy_t InformationGain::calcInforGain(const Coordinate & candidate, const Hypotheses & current_hyps, const Hypotheses & future_hyps) const{
        entropy_t ret_sum = 0.0;
        
        for (auto i=0; i < current_hyps.size(); i++) {
			auto copy_futures = future_hyps;
			auto assumed_detection = backward_.calcGaussianBlurMean(candidate, *(copy_futures[i].getMethaneCells()), map_);

			vector<double> probs;
			for (auto const & hyp : copy_futures) {
				auto likehood = backward_.calcLikehood(hyp, candidate, assumed_detection, map_);
				probs.push_back(likehood * hyp.getProbability());
			}
			backward_.normalize(copy_futures, probs);

            ret_sum += (entropy(current_hyps) - entropy(copy_futures)) * current_hyps[i].getProbability();
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
    vector<entropy_t> InformationGain::calcInforGains(const vector<Coordinate> & candidates, const Hypotheses & hyps, int time_count) const{
        auto copy_hyps = make_shared<Hypotheses>(hyps);
        auto future_hyps = forward_.UpdateMethane(*copy_hyps, map_, time_count);
        
        vector<entropy_t> ret_vec;
        
        for(auto const & coord : candidates) {
            ret_vec.push_back(calcInforGain(coord, hyps, *future_hyps));
        }
        
        return ret_vec;
    }
}