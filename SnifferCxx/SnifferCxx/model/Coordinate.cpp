//
//  Coordinate.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Coordinate.h"
#include "WindVector.h"
#include <numeric>

namespace Model {
	using namespace std;

	Coordinate::Coordinate() {
		*this = coord_t{ { 0, 0, 0 } };
	}

	Coordinate::Coordinate(coord_item_t x, coord_item_t y, coord_item_t z) {
		*this = coord_t{ { x, y, z } };
	}
    
    double Coordinate::calcNorm() const {
        return sqrt(accumulate(begin(), end(), 0, [](coord_item_t ret_val, const coord_item_t & item_val){return ret_val += item_val * item_val;}));
    }

	Coordinate Coordinate::operator + (const Coordinate & oth) const {
		Coordinate ret;
		transform(oth.begin(), oth.end(), begin(), ret.begin(), [](const coord_item_t & it1, const coord_item_t & it2){return it1 + it2; });
		return ret;
	}
    
    Coordinate Coordinate::operator - (const Coordinate & oth) const {
		Coordinate ret;
		transform(oth.begin(), oth.end(), begin(), ret.begin(), [](const coord_item_t & it1, const coord_item_t & it2){return it2 - it1; });
		return ret;
	}
    
    WindVector Coordinate::operator / (const double & norm) const {
		WindVector ret;
		transform(begin(), end(), ret.begin(), [norm](const coord_item_t & it) {return it / norm; });
		return ret;
	}

	Coordinate & Coordinate::operator= (const coord_t & rhs) {
		if (this == &rhs) {
			return *this;
		}

		copy(rhs.begin(), rhs.end(), this->begin());

		return *this;
	}

	ostream& operator<<(ostream& os, const Coordinate& coord)
	{
		os << "(" << coord[0] << ", " << coord[1] << ", " << coord[2] << ")";

		return os;
	}
}