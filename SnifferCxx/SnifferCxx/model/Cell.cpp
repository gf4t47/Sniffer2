//
//  Cell.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Cell.h"

namespace Model {
	using namespace std;

	unordered_map<CellTag, string, enum_hash> Cell::TagString = { 
			{ CellTag::Air, "Air" }, 
			{ CellTag::Building, "Building" }, 
			{ CellTag::Ground, "Ground" } 
	};

	Cell::Cell()
		:coord_(Coordinate()),
		wind_(Wind()),
		mtn_(Methane()),
		tag_(CellTag::Air) {

	}

	Cell::Cell(Coordinate & coord, CellTag tag, Methane & mtn, Wind & wind)
		:coord_(coord),
		wind_(wind),
		mtn_(mtn),
		tag_(tag) {

	}

	const Wind & Cell::getWind() const {
		return wind_;
	}

	const Methane & Cell::getMethane() const {
		return mtn_;
	}

	const Coordinate & Cell::getCoordinate() const {
		return coord_;
	}

	CellTag Cell::getTag() const{
		return tag_;
	}

	bool Cell::isAirCell() const {
		return getTag() == CellTag::Air;
	}

	bool Cell::hasMethane() const {
		return mtn_.getConcentration() > 0;
	}

	bool Cell::setMethane(const Methane & mtn) {
		mtn_ = mtn;
		return true;
	}

	bool Cell::setCellTag(const CellTag & tag) {
		tag_ = tag;
		return true;
	}
    
    bool Cell::setWindVector(const shared_ptr<WindVector> wind) {
        return wind_.setWindVector(wind);
    }
    
    bool Cell::setCoordinate(const Coordinate &coord) {
        coord_ = coord;
        return true;
    }
    
    bool Cell::setPotential(const WindVector &potential) {
        return wind_.setPotential(potential);
    }

	bool Cell::operator== (const Cell & oth) const {
		return coord_ == oth.coord_
			&& wind_ == oth.wind_
			&& tag_ == oth.tag_;
	}

	ostream& operator<<(ostream& os, const Cell& cell)
	{
		os << "{" << endl;
		os << " Coord: " << cell.coord_ << endl;
		os << " Tag: " << Cell::TagString[cell.tag_] << endl;
		os << " Wind: " << cell.wind_ << endl;
		os << " Methane: " << cell.mtn_ << endl;
		os << "}" << endl;

		return os;
	}
}