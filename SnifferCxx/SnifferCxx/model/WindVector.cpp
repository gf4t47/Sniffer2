//
//  WindVector.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "WindVector.h"
#include "Coordinate.h"
#include <numeric>
#include <fstream>
#include <sstream>

namespace Model {
	using namespace std;

	WindVector::WindVector() {
		*this = wv_t{ { 0, 0, 0 } };

	}

	WindVector::WindVector(wv_item_t x, wv_item_t y, wv_item_t z) {
		*this = wv_t{ { x, y, z } };
	}

    wv_item_t WindVector::calcNorm() const {
        return sqrt(accumulate(begin(), end(), 0.0f, [](wv_item_t ret_val, const wv_item_t & item_val){return ret_val += item_val * item_val;}));
    }
    
	WindVector WindVector::operator + (const WindVector &rhs) const{
		WindVector ret;
		transform(rhs.begin(), rhs.end(), begin(), ret.begin(), [](const wv_item_t & it1, const wv_item_t & it2){return it1 + it2; });
		return ret;
	}

	WindVector WindVector::operator - (const WindVector & rhs) const {
		WindVector ret;
		transform(rhs.begin(), rhs.end(), begin(), ret.begin(), [](const coord_item_t & it1, const coord_item_t & it2){return it2 - it1; });
		return ret;
	}

	Coordinate WindVector::operator / (const unit_t & unit) const {
		Coordinate ret;
		transform(begin(), end(), ret.begin(), [unit](const wv_item_t & it) {return it / unit; });
		return ret;
	}

	WindVector WindVector::operator % (const unit_t & unit) const {
		WindVector ret;
		transform(begin(), end(), ret.begin(), [unit](const wv_item_t & it) {return fmod(it, unit); });
		return ret;
	}

	WindVector WindVector::operator * (const wv_item_t & factor) const {
		WindVector ret;
		transform(begin(), end(), ret.begin(), [factor](const wv_item_t & it) {return it * factor; });
		return ret;
	}

	WindVector & WindVector::operator= (const wv_t & rhs) {
		if (this == &rhs) {
			return *this;
		}

		copy(rhs.begin(), rhs.end(), this->begin());

		return *this;
	}

	ostream& operator<<(ostream& os, const WindVector& wv)
	{
		os << "(" << wv[0] << ", " << wv[1] << ", " << wv[2] << ")";

		return os;
	}

	ofstream& operator<<(ofstream& fs, const WindVector& wv) {
	
		fs << wv[0] << wv[1] << wv[2];

		return fs;
	}
}
