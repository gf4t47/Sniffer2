//
//  WindVector.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "WindVector.h"
#include "Coordinate.h"

namespace Model {
	using namespace std;

	WindVector::WindVector()
		:wv_t{ { 0.0f, 0.0f, 0.0f } } {

	}

	WindVector::WindVector(wv_item_t x, wv_item_t y, wv_item_t z)
		: wv_t{ { x, y, z } } {

	}

	WindVector WindVector::operator+(const WindVector &oth) const{
		WindVector ret;
		transform(oth.begin(), oth.end(), begin(), ret.begin(), [](wv_item_t it1, wv_item_t it2){return it1 + it2; });
		return ret;
	}

	//WindVector WindVector::operator+(const Coordinate &oth) const{
	//	WindVector ret;
	//	transform(oth.begin(), oth.end(), begin(), ret.begin(), [](coord_item_t it1, wv_item_t it2){return it1 + it2; });
	//	return ret;
	//}

	Coordinate WindVector::operator/(const unit_t & unit) const {
		Coordinate ret;
		transform(begin(), end(), ret.begin(), [unit](wv_item_t it) {return it / unit; });
		return ret;
	}

	ostream& operator<<(ostream& os, const WindVector& wv)
	{
		os << "(" << wv[0] << ", " << wv[1] << ", " << wv[2] << ")";

		return os;
	}
}
