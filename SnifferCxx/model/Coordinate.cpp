//
//  Coordinate.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Coordinate.h"
#include "WindVector.h"

namespace Model {
	using namespace std;

	Coordinate::Coordinate()
		:coord_t{ { 0, 0, 0 } } {

	}

	Coordinate::Coordinate(coord_item_t x, coord_item_t y, coord_item_t z)
		: coord_t{ { x, y, z } } {

	}

	Coordinate Coordinate::operator+ (const Coordinate & oth) const {
		Coordinate ret;
		transform(oth.begin(), oth.end(), begin(), ret.begin(), [](coord_item_t it1, coord_item_t it2){return it1 + it2; });
		return ret;
	}

	ostream& operator<<(ostream& os, const Coordinate& coord)
	{
		os << "(" << coord[0] << ", " << coord[1] << ", " << coord[2] << ")";

		return os;
	}
}