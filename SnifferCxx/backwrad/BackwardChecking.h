//
//  BackwardChecking.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__BackwardChecking__
#define __SnifferCxx__BackwardChecking__
#include <memory>
#include <vector>
#include "../model/Hypothesis.h"

namespace Forward {
    class ForwardChecking;
}

namespace Model {
    class Map3D;
    class Coordinate;
}

namespace Backward {
    class BackwardChecking {
    public:
        BackwardChecking();
        virtual ~BackwardChecking();
        
        std::shared_ptr<std::vector<Model::Hypothesis>> updateHypotheses(const std::vector<Model::Hypothesis> & hyps, const Model::Map3D & map, size_t time_count, const std::vector<Model::Leak> & detections) const;
        
    protected:
        double calcLikehood(const Model::Hypothesis & hyp, const Model::Coordinate & detected_location, double detected_concentration, const Model::Map3D & map) const;
        void normalize(std::vector<Model::Hypothesis> & hyps) const;
        
    private:
        std::unique_ptr<Forward::ForwardChecking> forward_;
    };
}

#endif /* defined(__SnifferCxx__BackwardChecking__) */
