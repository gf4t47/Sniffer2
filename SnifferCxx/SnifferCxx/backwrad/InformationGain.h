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
        InformationGain(const Forward::ForwardChecking & forward, const BackwardChecking & backward, Model::Map3D & map);
        virtual ~InformationGain();
        
        std::vector<entropy_t> calcInforGains(const std::vector<Model::Coordinate> & candidates, const std::vector<Model::Hypothesis> & hyps, int time_count) const;
        
    private:
        entropy_t calcInforGain(const Model::Coordinate & candidate, const std::vector<Model::Hypothesis> & hyps, std::vector<Model::Hypothesis> & future_hyps) const;
        double calcLikehood(const Model::Hypothesis & hyp, const Model::Coordinate & detected_location, const Model::Map3D & map) const;
        entropy_t entropy(const Model::Hypothesis & hyp) const;
        
    private:
        const Forward::ForwardChecking & forward_;
        const BackwardChecking & backward_;
        Model::Map3D & map_;
    };
}

#endif /* defined(__SnifferCxx__InformationGain__) */
