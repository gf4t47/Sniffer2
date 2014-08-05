//
//  InformationGain.h
//  SnifferCxx
//
//  Created by Ke Ding  on 8/5/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__InformationGain__
#define __SnifferCxx__InformationGain__

#include <vector>

namespace Model {
    class Coordinate;
    class Hypothesis;
}

namespace Backward {
    typedef double score_t;
    typedef double entropy_t;
    
    class InformationGain {
    public:
        std::vector<score_t> calcInforGain(const std::vector<Model::Coordinate> & candidates, const std::vector<Model::Hypothesis> & hyps) const;
        
    private:
        std::vector<Model::Hypothesis> updateHypothesis(const Model::Coordinate & cadidate, const std::vector<Model::Hypothesis> & hyps) const;
        entropy_t entropy(const Model::Hypothesis & hyp) const;
        score_t calcInforGain(const Model::Coordinate & cadidate, const std::vector<Model::Hypothesis> & hyps) const;
    };
}

#endif /* defined(__SnifferCxx__InformationGain__) */
