//
//  WindVector.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "WindVector.h"

namespace Model {
    using namespace std;

	WindVector::WindVector()
    :wv_t{0.0f,0.0f,0.0f} {

	}

	WindVector::WindVector(double x, double y, double z)
    :wv_t{x,y,z} {
        
	}
    
    WindVector WindVector::operator+(const Model::WindVector &oth) const{
        WindVector ret;
        transform(oth.begin(), oth.end(), begin(), ret.begin(), [](double it1, double it2){return it1 + it2;});
        return ret;
    }
    
    ostream& operator<<(ostream& os, const WindVector& wv)
    {
        os << "("<<wv[0] <<", "<<wv[1]<<", "<<wv[2]<<")";
        
        return os;
    }
}
