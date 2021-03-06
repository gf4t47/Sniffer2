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

//#include "../model/TypeDef.h"

namespace Model
{
	class Coordinate;
	class Map3D;
	class Cells;
	class Cell;
}

namespace Math
{
	typedef boost::multi_array<double, 3> kernel_t;

	class GaussianBlur
	{
	public:
		static std::shared_ptr<Model::Cells> blurCell(const Model::Cell& ori_cell, const Model::Map3D& map, int kernel_range);
		static std::shared_ptr<Model::Cells> blurCells(const Model::Coordinate& location, int step, const Model::Cells& methane_cells, const Model::Map3D& map, int kernel_range);
		static std::shared_ptr<kernel_t> generateGaussianKernel(int step);
		static double gaussian_pdf(const Model::Coordinate& mean, int step, const Model::Coordinate& val);

	private:
		static void resetStaticKernel(int kernel_range);

	public:
		static int static_kernel_range;
		static std::shared_ptr<kernel_t> static_kernel;

	private:
		static std::string kernelToString(const kernel_t& kernel);
	};
}

#endif /* defined(__SnifferCxx__GaussianBlur__) */