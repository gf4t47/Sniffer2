//
//  GaussianBlur.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "GaussianBlur.h"
#include <math.h>
#include <boost/math/distributions/normal.hpp>
#include <boost/fusion/include/zip.hpp>
#include <numeric>
#include "../model/Map3D.h"
#include "../model/Cells.h"


namespace Math {
	using namespace std;
	using namespace Model;

	const size_t blur_step = 2;
	const auto static_kernel = *GaussianBlur::generateGaussianKernel(blur_step);

	double GaussianBlur::gaussian_pdf(const Model::Coordinate &mean, int step, const Model::Coordinate &val) {
		typedef boost::math::normal::normal_distribution<> distribution_t;

		auto dists = accumulate(mean.begin(), mean.end(), vector<distribution_t>(), [step](vector<distribution_t> ret_vec, const coord_item_t & item_val){ret_vec.push_back(distribution_t(item_val, step)); return ret_vec; });

		double ret = 1.0;
		for (auto i = 0; i < val.size(); i++) {
			ret *= boost::math::pdf(dists[i], val[i]);
		}

		return ret;
	}

	shared_ptr<kernel_t> GaussianBlur::generateGaussianKernel(int step) {
		auto kernel = make_shared<kernel_t>();
		kernel->reindex(-step);

		Coordinate mean(0, 0, 0);
		for (auto l = -step; l <= step; l++) {
			for (auto w = -step; w <= step; w++) {
				for (auto h = -step; h <= step; h++) {
					Coordinate coord(l, w, h);
					(*kernel)(coord) = gaussian_pdf(mean, step, coord);
				}
			}
		}

		return kernel;
	}

	shared_ptr<Cells> GaussianBlur::blurCells(const Map3D & map, const Coordinate &location, const Cells &cells, int step) {
		step = blur_step;
		auto kernel = static_kernel;
		for (auto l = location[0] - step; l <= location[0] + step; l++) {
			for (auto w = location[1] - step; w <= location[1] + step; w++) {
				for (auto h = location[2] - step; h <= location[2] + step; h++) {
					Coordinate cell_coord(l, w, h);
					Coordinate kernel_coord(l - location[0], w - location[1], h - location[2]);
					if (!map.isAirCell(cell_coord)) {
						kernel(kernel_coord) = 0;
					}
				}
			}
		}

		boost::multi_array_ref<double, 1> kernel_ref(kernel.data(), boost::extents[kernel.num_elements()]);
		auto sum = accumulate(kernel_ref.begin(), kernel_ref.end(), 0.0);
		if (sum <= 0) {
			return make_shared<Cells>(cells);
		}

		auto ret_cells = make_shared<Cells>();

		for_each(kernel_ref.begin(), kernel_ref.end(), [sum](double & item){item /= sum; });
		for (auto l = location[0] - step; l <= location[0] + step; l++) {
			for (auto w = location[1] - step; w <= location[1] + step; w++) {
				for (auto h = location[2] - step; h <= location[2] + step; h++) {
					Coordinate cell_coord(l, w, h);
					auto cell = map.getCell(cell_coord);
				}
			}
		}
		return ret_cells;
	}
}