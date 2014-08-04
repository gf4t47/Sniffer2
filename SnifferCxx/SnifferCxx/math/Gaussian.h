//
//  Gaussian.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__Gaussian__
#define __SnifferCxx__Gaussian__

#include <memory>
#include <vector>
#include "../model/WindVector.h"

namespace Math {
    class Gaussian {
    public:
		static std::shared_ptr<std::vector<Model::WindVector>> RandomWindVectors(const Model::WindVector & mean, const Model::unit_t range, const size_t num);
    };
}



#endif /* defined(__SnifferCxx__Gaussian__) */
