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

namespace Backward {
    using namespace std;
    using namespace Model;

    entropy_t InformationGain::entropy(const Hypothesis & hyp) const{
        return -(hyp.getProbability() * log2(hyp.getProbability()));
    }
    
    score_t InformationGain::calcInforGain(const Coordinate & cadidate, const vector<Hypothesis> &hyps) const{
        return 0.0;
    }
    
    vector<score_t> InformationGain::calcInforGain(const vector<Coordinate> & candidates, const vector<Hypothesis> & hyps) const{
        vector<score_t> ret_vec;
        
        for(auto const & coord : candidates) {
            ret_vec.push_back(calcInforGain(coord, hyps));
        }
        
        return ret_vec;
    }
    
    vector<Hypothesis> InformationGain::updateHypothesis(const Coordinate & cadidate, const vector<Hypothesis> & hyps) const {
        vector<Hypothesis> ret_vec;
        
        return ret_vec;
    }
}