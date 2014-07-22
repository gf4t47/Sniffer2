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

namespace Model {
    class Coordinate;
    class Cells;
	class Map3D;
}

namespace Math {
    class GaussianBlur {
    public:
        static std::shared_ptr<Model::Cells> BlurCells(const Model::Map3D & map, const Model::Coordinate & location, const Model::Cells & cells, size_t step);
        
        static void gaussianiir3d(double *volume, long width, long height, long depth, double sigma, int numsteps = 4);
    };
}

#endif /* defined(__SnifferCxx__GaussianBlur__) */