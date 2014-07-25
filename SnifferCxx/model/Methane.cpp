//
//  Methane.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Methane.h"

namespace Model {
	using namespace std;

	const double background = 0.25;

	Methane::Methane()
		:concentration_(0.0f) {

	}

	Methane::Methane(mtn_t c)
		: concentration_(c) {

	}

	double Methane::getBackground() {
		return background;
	}

	mtn_t Methane::getParticleNum() const {
		return concentration_;
	}

	double Methane::getMethane() const {
		return getParticleNum() + getBackground();
	}

	bool Methane::updateMethane(mtn_t concentration) {
		concentration_ = concentration;

		return true;
	}

	bool Methane::operator== (const Methane & oth) const {
		return concentration_ == oth.concentration_;
	}

	ostream& operator<<(ostream& os, const Methane& mtn)
	{
		os << "{" << mtn.concentration_ << " + " << background << "}";

		return os;
	}
}