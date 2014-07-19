//
//  UpdateByCell.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__UpdateByCell__
#define __SnifferCxx__UpdateByCell__

#include <iostream>
#include "ForwardChecking.h"

namespace Forward {
    
    typedef std::unordered_map<Model::Coordinate, size_t, Model::CoordHasher> pos_val_st;
    
    class UpdateByCell : public ForwardChecking {
    public:
        ~UpdateByCell();
        
        std::shared_ptr<Model::Cells> Deduce(const std::shared_ptr<Model::Cells> cells, const Model::Map3D & map, size_t count) const;
        
    protected:
        std::shared_ptr<Model::Cells> calcEnds(const Model::Cell & cell, const Model::Map3D & map) const;
        
    private:
        std::shared_ptr<pos_val_st> calcGaussianEnds(const Model::Coordinate & startPos,const Model::WindVector & wv, const Model::mtn_t particle_num, const Model::Map3D & map) const;
        std::shared_ptr<std::vector<Model::WindVector>> calcGaussianSamples(const Model::WindVector & mean, const Model::unit_t unit, const size_t num) const;
        
    };
}

#endif /* defined(__SnifferCxx__UpdateByCell__) */
