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
     *  calculate information gain by sum the entropy for all hypotheses together for one candidate
     *
     *  @param candidate one coordinate candidate for detection
     *  @param hyps      all virtual worlds represent all the hypotheses
     *
     *  @return expected information gain
     */
    entropy_t InformationGain::calcInforGain(const Coordinate & candidate, const vector<Hypothesis> & hyps, vector<Hypothesis> & future_hyps) const{
        vector<double> probs;
        for (auto const & hyp : future_hyps) {
            auto prob = calcLikehood(hyp, candidate, map_) * hyp.getProbability();
            probs.push_back(prob);
        }
        backward_.normalize(future_hyps, probs);
        
        entropy_t ret_sum = 0.0;
        
        for (auto i=0; i < hyps.size(); i++) {
            ret_sum += (entropy(hyps[i]) - entropy(future_hyps[i])) * hyps[i].getProbability();
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