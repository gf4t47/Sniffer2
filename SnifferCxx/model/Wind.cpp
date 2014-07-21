//
//  Wind.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Wind.h"

namespace Model {
	using namespace std;

	Wind::Wind()
		:potential_(WindVector()),
		wind_(WindVector()) {

	}

	Wind::Wind(const WindVector & wind)
		: wind_(wind),
		potential_(WindVector()) {

	}

	Wind::Wind(const WindVector & wind, const WindVector & potential)
		: potential_(potential),
		wind_(wind) {

	}

	WindVector Wind::getWindVector() const {
		return wind_ + potential_;
	}

	bool Wind::operator== (const Wind & oth) const {
		return wind_ == oth.wind_ && potential_ == oth.potential_;
	}

	ostream& operator<<(ostream& os, const Wind& wind)
	{
		os << "{" << wind.wind_ << " + " << wind.potential_ << "}";

		return os;
	}
}