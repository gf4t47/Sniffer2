//
//  GaussianBlur.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__GaussianBlur__
#define __SnifferCxx__GaussianBlur__

#include <memory>
#include <boost/multi_array.hpp>

namespace Model {
    class Coordinate;
    class Map3D;
    class Cells;
}

namespace Math {
    typedef boost::multi_array<double, 3> kernel_t;
    class GaussianBlur {
    public:
        static std::shared_ptr<Model::Cells> blurCell(const Model::Coordinate & location, const double concentration, const Model::Map3D & map);
        static std::shared_ptr<Model::Cells> blurCells(const Model::Coordinate & location, int step, const Model::Cells & methane_cells, const Model::Map3D & map);
        static std::shared_ptr<kernel_t> generateGaussianKernel(int step);
        static double gaussian_pdf(const Model::Coordinate & mean, int step, const Model::Coordinate & val);

	private:
		static std::string kernelToString(const kernel_t & kernel);
    };
}

#endif /* defined(__SnifferCxx__GaussianBlur__) */
