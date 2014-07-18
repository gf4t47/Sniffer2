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

	WindVector::WindVector() {

	}

	WindVector::WindVector(double x, double y, double z) {
		this->at(0) = x;
		this->at(1) = y;
		this->at(2) = z;
	}
    
    WindVector WindVector::operator+(const Model::WindVector &oth) {
        WindVector ret;
        transform(oth.begin(), oth.end(), begin(), ret.begin(), [](double it1, double it2){return it1 + it2;});
        return ret;
    }
}
