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

	mtn_t Methane::background_ = 0.05;
	mtn_t Methane::concentration_per_particle_ = 0.00003;

	Methane::Methane()
		:particles_(0),
		potential_(WindVector(0, 0, 0)) {
	}

	Methane::Methane(mtn_t p)
		: particles_(p),
		potential_(WindVector(0, 0, 0)) {

	}

	Methane::Methane(mtn_t p, const WindVector & wv)
		:particles_(p),
		potential_(wv){

	}

	double Methane::getBackground() {
		return background_;
	}

	double Methane::getConcPerParticle() {
		return concentration_per_particle_;
	}

	void Methane::setBackgournd(double val) {
		background_ = val;
	}

	void Methane::setConcPerParticle(double val) {
		concentration_per_particle_ = val;
	}

	mtn_t Methane::getParitcles() const {
		return particles_;
	}

	const WindVector & Methane::getPotential() const {
		return potential_;
	}

	mtn_t Methane::getMethaneConc() const {
		return getParitcles() * getConcPerParticle() + getBackground();
	}

	Methane Methane::operator+ (const Methane & oth) const {
		return Methane(particles_ + oth.particles_, (potential_ + oth.potential_) * 0.5);
	}

	ostream& operator<<(ostream& os, const Methane& mtn)
	{
		os << "{" << mtn.particles_ << " + " << mtn.background_ << "}";

		return os;
	}

	ofstream& Methane::toBinary(ofstream& fs) const{
		auto con = static_cast<double>(getParitcles());
		fs.write(reinterpret_cast<char*>(&con), sizeof con);

		return fs;
	}
}