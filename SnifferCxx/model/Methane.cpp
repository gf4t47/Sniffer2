//
//  Methane.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Methane.h"

namespace Model {
    const double background = 0.25;
    
    Methane::Methane()
    :concentration_(0.0f) {
        
    }
    
    Methane::Methane(mtn_t c)
    :concentration_(c) {
        
    }
    
    double Methane::getBackground() {
        return background;
    }
    
    mtn_t Methane::getParticleNum() {
        return concentration_;
    }
    
    double Methane::getMethane() {
        return getParticleNum() + getBackground();
    }
}