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
#include <memory>

namespace Model {
    class Coordinate;
    class Hypothesis;
    class Map3D;
}

namespace Forward {
    class ForwardChecking;
}

namespace Backward {
    typedef double entropy_t;
    
    class BackwardChecking;
    
    class InformationGain {
    public:
        InformationGain(const Forward::ForwardChecking & forward, const BackwardChecking & backward, const Model::Map3D & map, size_t count);
        virtual ~InformationGain();
        
        entropy_t calcInforGain(const Model::Coordinate & candidate, const std::vector<Model::Hypothesis> & hyps) const;
        std::vector<entropy_t> calcInforGain(const std::vector<Model::Coordinate> & candidates, const std::vector<Model::Hypothesis> & hyps) const;
        
    private:
        std::shared_ptr<std::vector<Model::Hypothesis>> updateHypothesis(const Model::Coordinate & candidate, const std::vector<Model::Hypothesis> & hyps) const;
        double calcLikehood(const Model::Hypothesis & hyp, const Model::Coordinate & detected_location, const Model::Map3D & map) const;
        entropy_t entropy(const Model::Hypothesis & hyp) const;
        
    private:
        const Forward::ForwardChecking & forward_;
        const BackwardChecking & backward_;
        const Model::Map3D & map_;
        size_t time_count_;
    };
}

#endif /* defined(__SnifferCxx__InformationGain__) */
