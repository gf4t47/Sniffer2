//
//  Methane.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Methane__
#define __Sniffer_Cxx__Methane__

#include <iostream>

namespace Model {
    typedef double mtn_t;
    
    class Methane {
    public:
        Methane();
        Methane(mtn_t c);
        
        double getMethane();
        mtn_t getParticleNum();
        double getBackground();
        
    private:
        mtn_t concentration_;
    };
}

#endif /* defined(__Sniffer_Cxx__Methane__) */
