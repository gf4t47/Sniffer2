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
     *  @param count    how long you assume for the future || how much iterations you will push the forward checking algorith
     */
    InformationGain::InformationGain(const ForwardChecking & forward, const BackwardChecking & backward, const Map3D & map, size_t count)
    :forward_(forward),
    backward_(backward),
    map_(map),
    time_count_(count) {
        
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
    entropy_t InformationGain::entropy(const Hypothesis & hyp) const{
        return -(hyp.getProbability() * log2(hyp.getProbability()));
    }
    
    
    /**
     *  calculate gamma likehood
     *
     *  @param hyp               the virtual world under this hypothesis
     *  @param detected_location one coordiante candidate for detection
     *  @param map               our map model
     *
     *  @return probability for this detection
     */
    double InformationGain::calcLikehood(const Hypothesis & hyp, const Coordinate & detected_location, const Map3D & map) const {
        auto mean = backward_.calcGaussianBlurMean(detected_location, *hyp.getMethaneCells(), map);
        return Math::Gamma::calcGammaPdf(mean, mean);
    }
    
    
    /**
     *  update our forward model, calculate the new probability for all hypotheses
     *
     *  @param candidate push all the hypothses update seerval steps and active one candiate detection
     *  @param hyps      all virtual worlds for all the hypotheses
     *
     *  @return the updated hypohteses with new probability in futrue time
     */
    shared_ptr<vector<Hypothesis>> InformationGain::updateHypothesis(const Coordinate & candidate, const vector<Hypothesis> & hyps) const {
        auto copy_hyps = make_shared<vector<Hypothesis>>(hyps);
        
        forward_.UpdateMethane(*copy_hyps, map_, time_count_);
        
        vector<double> probs;
        for (auto const & hyp : *copy_hyps) {
            auto prob = calcLikehood(hyp, candidate, map_) * hyp.getProbability();
            probs.push_back(prob);
        }
        
        backward_.normalize(*copy_hyps, probs);

        return copy_hyps;
    }
    
    
    /**
     *  calculate information gain by sum the entropy for all hypotheses together for one candidate
     *
     *  @param candidate one coordinate candidate for detection
     *  @param hyps      all virtual worlds represent all the hypotheses
     *
     *  @return expected information gain
     */
    entropy_t InformationGain::calcInforGain(const Coordinate & candidate, const vector<Hypothesis> & hyps) const{
        auto new_hyps = updateHypothesis(candidate, hyps);
        
        entropy_t ret_sum = 0.0;
        
        for (auto i=0; i < hyps.size(); i++) {
            ret_sum += (entropy(hyps[i]) - entropy((*new_hyps)[i])) * hyps[i].getProbability();
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
    vector<entropy_t> InformationGain::calcInforGain(const vector<Coordinate> & candidates, const vector<Hypothesis> & hyps) const{
        vector<entropy_t> ret_vec;
        
        for(auto const & coord : candidates) {
            ret_vec.push_back(calcInforGain(coord, hyps));
        }
        
        return ret_vec;
    }
}