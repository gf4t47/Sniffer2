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
#include "../model/TypeDef.h"

namespace Support {
	class MyLog;
}

namespace Forward {
    class ForwardChecking;
}

namespace Model {
    class Map3D;
    class Coordinate;
	class Cells;
	class Hypothesis;
	class Hypotheses;

	struct Candidate;
}

namespace Backward {
	using Model::range_t;

	class BackwardChecking {
    public:
        BackwardChecking(range_t gaussian_blur_range, range_t gaussian_kernel_range, range_t gamma_variance);
        virtual ~BackwardChecking();
        
        Model::mtn_t calcGaussianBlurMean(const Model::Coordinate & location, const Model::Cells & methane_cells, const Model::Map3D & map) const;
        void normalize(Model::Hypotheses & hyps, const std::vector<double> & hyps_probability) const;
        std::shared_ptr<Model::Hypotheses> updateHypotheses(Model::Hypotheses & hyps, const Model::Map3D & map, const std::vector<Model::Candidate> & detections) const;
		double calcLikehood(const Model::Hypothesis & hyp, const Model::Coordinate & detected_location, double detected_particles, const Model::Map3D & map) const;

	private:
		range_t getBlurRange() const;
        range_t getKernelRange() const;
        
    private:
		range_t gaussian_blur_range_;
        range_t gaussian_kernel_range_;
		range_t gamma_variance_;
		static std::unique_ptr<Support::MyLog> lg_;
    };
}

#endif /* defined(__SnifferCxx__BackwardChecking__) */
