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
    
    double GaussianBlur::gaussian_pdf(const Model::Coordinate &mean, int step, const Model::Coordinate &val) {
        typedef boost::math::normal::normal_distribution<coord_item_t> distribution_t;
        
        auto dists = accumulate(mean.begin(), mean.end(), vector<distribution_t>(), [step](vector<distribution_t> ret_vec, const coord_item_t & item_val){ret_vec.push_back(distribution_t(item_val, step)); return ret_vec;});

        double ret = 1.0;
        for (auto i =0 ; i < val.size(); i++) {
            ret *= pdf(dists[i], val[i]);
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
		auto ret_cells = make_shared<Cells>();

//		auto locate_x = location[0];
//		auto locate_y = location[1];
//		auto locate_z = location[2];
//		auto size = step * 2 + 1;
//
//		auto index = 0;
//		unique_ptr<double[]> arr(new double[size * size * size]);
//		for (int h = -step; h < -step + size; h++)  {
//			for (int w = -step; w < -step + size; w++) {
//				for (int l = -step; l < -step + size; l++){
//					auto cell_x = locate_x + l;
//					auto cell_y = locate_y + w;
//					auto cell_z = locate_z + h;
//
//					auto cell = cells.getCell(cell_x, cell_y, cell_z);
//					if (cell) {
//						arr[index++] = cell->getMethane().getParticleNum();
//					}
//					else {
//						arr[index++] = 0;
//					}
//				}
//			}
//        }
//
//		index = 0;
//		gaussianiir3d(arr.get(), size, size, size, step);
//		for (int h = -step; h < -step + size; h++)  {
//			for (int w = -step; w < -step + size; w++) {
//				for (int l = -step; l < -step + size; l++){
//					auto cell_x = locate_x + l;
//					auto cell_y = locate_y + w;
//					auto cell_z = locate_z + h;
//
//					auto bluredVal = arr[index++];
//					if (bluredVal > 0) { 	
//						Coordinate coord(cell_x, cell_y, cell_z);
//						if (map.insideMap(coord)) {
//							auto newCell = map.getCell(coord);
//							newCell.setMethaneConcentration(bluredVal);
//							ret_cells->updateCell(newCell);
//						}
//					}
//				}
//			}
//		}

		return ret_cells;
    }
}