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

    int GaussianBlur::static_kernel_range = 2;
	auto GaussianBlur::static_kernel = *GaussianBlur::generateGaussianKernel(static_kernel_range);

	std::string GaussianBlur::kernelToString(const kernel_t & kernel) {
		auto index = kernel.index_bases();
		auto length = kernel.shape();
		
		ostringstream ostr;

		ostr << "kernel: " << endl;
		for (auto l = index[0]; l < index[0] + (int)length[0]; l++) {
			for (auto w = index[1]; w < index[1] + (int)length[1]; w++) {
				ostr << "[";
				for (auto h = index[2]; h < index[2] + (int)length[2]; h++) {
					ostr << kernel[l][w][h] << ", ";
				}
				ostr << "]";
			}
			ostr << endl;
		}

		return ostr.str();
	}

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
        auto kernel_size = step * 2 + 1;
		auto kernel = make_shared<kernel_t>(boost::extents[kernel_size][kernel_size][kernel_size]);
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
    
    shared_ptr<Cells> GaussianBlur::blurCell(const Coordinate &location, const double concentration, const Map3D &map, int kernel_range) {
		auto kernel = static_kernel;
		auto step = static_kernel_range;

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
        
        auto ret_cells = make_shared<Cells>();
		boost::multi_array_ref<double, 1> kernel_ref(kernel.data(), boost::extents[kernel.num_elements()]);
		auto sum = accumulate(kernel_ref.begin(), kernel_ref.end(), 0.0);
		if (sum <= 0) {
            auto cell = map.getCell(location);
            cell.setMethaneConcentration(concentration);
            ret_cells->clear();
            ret_cells->updateCell(cell);
            return ret_cells;
		}
        
		//cout << kernelToString(kernel);
		for_each(kernel_ref.begin(), kernel_ref.end(), [sum](double & item){item /= sum; });
		//cout << kernelToString(kernel);
		//cout << kernelToString(static_kernel);
		for (auto l = location[0] - step; l <= location[0] + step; l++) {
			for (auto w = location[1] - step; w <= location[1] + step; w++) {
				for (auto h = location[2] - step; h <= location[2] + step; h++) {
					Coordinate cell_coord(l, w, h);
                    Coordinate kernel_coord(l - location[0], w - location[1], h - location[2]);
                    auto factor = kernel(kernel_coord);
                    if (factor > 0) {
                        auto cell = map.getCell(cell_coord);
                        cell.setMethaneConcentration(concentration * factor);
                        ret_cells->updateCell(cell);
                    }
				}
			}
		}
		return ret_cells;
    }

	shared_ptr<Cells> GaussianBlur::blurCells(const Coordinate &location, int step, const Cells &methane_cells, const Map3D & map, int kernel_range) {
        auto ret_cells = make_shared<Cells>();
        for (auto l = location[0] - step; l <= location[0] + step; l++) {
			for (auto w = location[1] - step; w <= location[1] + step; w++) {
				for (auto h = location[2] - step; h <= location[2] + step; h++) {
					Coordinate coord(l, w, h);
                    auto methane_cell = methane_cells.getCell(coord);
                    if (methane_cell && methane_cell->hasMethane()) {
                        auto new_cells = blurCell(coord, methane_cell->getMethane().getParticleNum(), map, kernel_range);
                        ret_cells->mergeCellsByAddMethane(*new_cells);
                    }
				}
			}
		}
        return ret_cells;
	}
}