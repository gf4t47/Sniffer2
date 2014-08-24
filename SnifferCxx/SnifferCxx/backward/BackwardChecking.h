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
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include "../model/TypeDef.h"

namespace Forward {
    class ForwardChecking;
}

namespace Model {
    class Map3D;
    class Coordinate;
	class Cells;
	class Hypothesis;

	struct Candidate;
}

enum severity_level
{
    trace,
    debug,
    info,
    error,
    critical
};

namespace Backward {
	using Model::range_t;

	class BackwardChecking {
    public:
        BackwardChecking(range_t blur_range, range_t kernel_range);
        virtual ~BackwardChecking();
        
        double calcGaussianBlurMean(const Model::Coordinate & location, const Model::Cells & methane_cells, const Model::Map3D & map) const;
        void normalize(std::vector<Model::Hypothesis> & hyps, const std::vector<double> & hyps_probability) const;
        std::shared_ptr<std::vector<Model::Hypothesis>> updateHypotheses(std::vector<Model::Hypothesis> & hyps, const Model::Map3D & map, const std::vector<Model::Candidate> & detections) const;
		double calcLikehood(const Model::Hypothesis & hyp, const Model::Coordinate & detected_location, double detected_concentration, const Model::Map3D & map) const;

	private:
		range_t getBlurRange() const;
        range_t getKernelRange() const;
        
    private:
		range_t blur_range_;
        range_t kernel_range_;
		mutable boost::log::sources::severity_logger<severity_level> lg_;
    };
}

#endif /* defined(__SnifferCxx__BackwardChecking__) */
