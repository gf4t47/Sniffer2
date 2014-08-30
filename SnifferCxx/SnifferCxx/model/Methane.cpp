//
//  Methane.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Methane.h"
#include <fstream>
#include <sstream>

namespace Model {
	using namespace std;

	const double background = 0.05;

	Methane::Methane()
		:concentration_(0.0f),
		potential_(WindVector(0, 0, 0)) {
	}

	Methane::Methane(mtn_t c)
		: concentration_(c),
		potential_(WindVector(0, 0, 0)) {

	}

	Methane::Methane(mtn_t c, const WindVector & wv)
		:concentration_(c),
		potential_(wv){

	}

	double Methane::getBackground() {
		return background;
	}

	mtn_t Methane::getConcentration() const {
		return concentration_;
	}

	const WindVector & Methane::getPotential() const {
		return potential_;
	}

	double Methane::getMethane() const {
		return getConcentration() + getBackground();
	}

	bool Methane::updateConcentration(mtn_t concentration) {
		concentration_ = concentration;

		return true;
	}

	//bool Methane::operator== (const Methane & oth) const {
	//	return concentration_ == oth.concentration_ && potential_ == oth.potential_;
	//}

	Methane Methane::operator+ (const Methane & oth) const {
		return Methane(concentration_ + oth.concentration_, (potential_ + oth.potential_) * 0.5);
	}

	ostream& operator<<(ostream& os, const Methane& mtn)
	{
		os << "{" << mtn.concentration_ << " + " << background << "}";

		return os;
	}

	//ofstream& operator<<(ofstream& fs, const Methane& mtn) {
	//	fs.write(reinterpret_cast<char*>(&(double)mtn.concentration_), sizeof mtn.concentration_);
	//	return fs;
	//}
}