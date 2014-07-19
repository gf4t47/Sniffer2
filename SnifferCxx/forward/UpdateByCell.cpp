//
//  UpdateByCell.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "UpdateByCell.h"
#include <random>

namespace Forward {
    using namespace std;
    using namespace Model;
    
    UpdateByCell::~UpdateByCell() {
        
    }
    
    shared_ptr<vector<WindVector>> UpdateByCell::calcGaussianSamples(const WindVector & mean, const unit_t unit, const size_t num) const {
        default_random_engine generator;
        vector<normal_distribution<double>> distributions;
        for (auto m : mean) {
            distributions.push_back(normal_distribution<double>(m,unit));
        }
        
        auto ret = make_shared<vector<WindVector>>();
        for (int i=0; i<num; i++) {
            WindVector wv;
            for (int j=0; j<distributions.size(); j++) {
                wv[j] = distributions[j](generator);
            }
            ret->push_back(wv);
        }
        
        return ret;
    }
    
    shared_ptr<vector<pair<WindVector, size_t>>> UpdateByCell::calcGaussianEnds(const Coordinate & startPos, const WindVector & wv, const mtn_t particle_num, const unit_t unit) const {
        auto winds = calcGaussianSamples(wv,unit, particle_num);
        size_t particle_num_per_wind = 1;
        
        auto ret = make_shared<vector<pair<WindVector, size_t>>>();
        for_each(winds->begin(), winds->end(), [&ret, particle_num_per_wind, &startPos](WindVector & wv){ ret->push_back(make_pair(startPos + wv, particle_num_per_wind)); });
        return ret;
    }
    
    shared_ptr<Cells> UpdateByCell::calcEnds(const Cell & cell, const Map3D map) const {
        if (!cell.isAirCell()) {
            return make_shared<Cells>();
        }
        
        auto curPos = cell.getCoordinate();
        
        return nullptr;
    }
    
    shared_ptr<Cells> UpdateByCell::Deduce(const shared_ptr<Cells> cells, const Map3D & map, size_t count) const {
        if (!cells || cells->size() <= 0) {
            return make_shared<Cells>();
        }
        
        return nullptr;
    }
}