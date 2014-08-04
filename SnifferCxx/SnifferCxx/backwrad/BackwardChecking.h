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
    typedef int range_t;
    
    class BackwardChecking {
    public:
        BackwardChecking(range_t blur_range, range_t kernel_range);
        virtual ~BackwardChecking();
        
        std::shared_ptr<std::vector<Model::Hypothesis>> updateHypotheses(std::vector<Model::Hypothesis> & hyps, const Model::Map3D & map, size_t time_count, const std::vector<Model::Leak> & detections, const std::shared_ptr<Forward::ForwardChecking> forward) const;
        
    protected:
        double calcLikehood(const Model::Hypothesis & hyp, const Model::Coordinate & detected_location, double detected_concentration, const Model::Map3D & map) const;
        void normalize(std::vector<Model::Hypothesis> & hyps) const;

	private:
		double calcGaussianBlurMean(const Model::Coordinate & location, const Model::Cells & methane_cells, const Model::Map3D & map) const;
		range_t getBlurRange() const;
        range_t getKernelRange() const;
        
    private:
		range_t blur_range_;
        range_t kernel_range_;
    };
}

#endif /* defined(__SnifferCxx__BackwardChecking__) */
