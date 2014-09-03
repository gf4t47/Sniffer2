//
//  Wind.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Wind.h"
#include "../support/MyLog.h"
#include <sstream>
#include <fstream>

namespace Model {
	using namespace std;
	using namespace Support;

	unique_ptr<MyLog> Wind::lg_(make_unique<MyLog>());

	Wind::Wind()
		:potential_(WindVector()),
		wind_(nullptr) {

	}

	//Wind::Wind(const WindVector & wind)
	//	: wind_(wind),
	//	potential_(WindVector()) {

	//}

	//Wind::Wind(const WindVector & wind, const WindVector & potential)
	//	: potential_(potential),
	//	wind_(wind) {

	//}

	WindVector Wind::getCalcWind() const {
		if (!wind_) {
			ostringstream ostr;
			ostr << "wind_ pointer has not been initialized";

			BOOST_LOG_SEV(*lg_, severity_level::critical) << ostr.str();
			throw runtime_error(ostr.str());
		}

		return *wind_ + potential_;
	}
    
    WindVector Wind::getPotential() const {
        return potential_;
    }

	WindVector Wind::getWV() const {
		if (!wind_) {
			ostringstream ostr;
			ostr << "wind_ pointer has not been initialized";

			BOOST_LOG_SEV(*lg_, severity_level::critical) << ostr.str();
			throw runtime_error(ostr.str());
		}

		return *wind_;
	}
    
    bool Wind::setWindVector(const WindVector * wv) {
        wind_ = wv;
        return wind_ != nullptr;
    }
    
    bool Wind::setPotential(const WindVector &potential) {
        potential_ = potential;
        return true;
    }

	bool Wind::operator== (const Wind & oth) const {
		return wind_ == oth.wind_ && potential_ == oth.potential_;
	}

	ostream& operator<<(std::ostream& os, const Wind& wind) {
		os << "{";
		os << *wind.wind_;
		os << " + ";
		os << wind.potential_;
		os << "}";

		return os;
	}

	ofstream& Wind::toBinary(ofstream& fs) const{
		//wind_->toBinary(fs);
		//potential_.toBinary(fs);
		getCalcWind().toBinary(fs);

		return fs;
	}
}