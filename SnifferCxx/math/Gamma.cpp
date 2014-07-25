//
//  Gamma.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Gamma.h"
#include <boost/math/special_functions/gamma.hpp>

namespace Math {
    using namespace boost;
    
    double Gamma::calcGammaPdf(double shape, double scale, double detected) {
        return math::gamma_p_derivative(shape, detected / scale) / scale;
    }
}