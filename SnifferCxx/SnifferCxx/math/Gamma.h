//
//  Gamma.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__Gamma__
#define __SnifferCxx__Gamma__


namespace Math {
    const double default_gamma_scale = 1.0;
    
    class Gamma {
    public:
        static double calcGammaPdf(double detected, double mean, double variance = default_gamma_scale);
    };
}

#endif /* defined(__SnifferCxx__Gamma__) */
