//
//  Vector3D.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Vector3D__
#define __Sniffer_Cxx__Vector3D__

#include <iostream>

namespace Model {
    template <typename Elemtype> class Vector3D {
    public:
        Vector3D();
        Vector3D(Elemtype x, Elemtype y, Elemtype z);
        
        Elemtype getX();
        Elemtype getY();
        Elemtype getZ();
        
    protected:
        Elemtype x_;
        Elemtype y_;
        Elemtype z_;
    };
    
    template <typename Elemtype> Vector3D<Elemtype>::Vector3D()
    :x_(0),
    y_(0),
    z_(0) {
    
    }
    
    template <typename Elemtype> Vector3D<Elemtype>::Vector3D(Elemtype x, Elemtype y, Elemtype z)
    :x_(x),
    y_(y),
    z_(z) {
        
    }
    
    template <typename Elemtype> Elemtype Vector3D<Elemtype>::getX() {
        return x_;
    }
    
    template <typename Elemtype> Elemtype Vector3D<Elemtype>::getY() {
        return y_;
    }
    
    template <typename Elemtype> Elemtype Vector3D<Elemtype>::getZ() {
        return z_;
    }
}


#endif /* defined(__Sniffer_Cxx__Vector3D__) */
