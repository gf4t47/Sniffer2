//
//  Gamma.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__Gamma__
#define __SnifferCxx__Gamma__


namespace Stactistic {
    class Gamma {
    public:
        static double calcGammaPdf(double shape, double scale, double detected);
    };
}

#endif /* defined(__SnifferCxx__Gamma__) */
