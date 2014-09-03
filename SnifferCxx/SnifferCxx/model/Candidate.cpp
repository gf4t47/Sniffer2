#include "Candidate.h"
#include <fstream>
#include <sstream>

namespace Model {
	using namespace std;

	ostream& operator<<(ostream& os, const Candidate & can)
	{
		os << "{";
		os << can.location_;
		os << ":";
		os << can.concentration_;
		os << "}";

		return os;
	}

	ofstream& Candidate::toBinary(ofstream& fs) const{
		location_.toBinary(fs);
		auto con = concentration_;
		fs.write(reinterpret_cast<char*>(&con), sizeof con);

		return fs;
	}

	ostream& operator<<(ostream& os, const Detection & dect)
	{
		os << "{";

		os << "time:" << dect.time_ << ", ";

		os << "wind:";
		if (dect.wv_) {
			os << *dect.wv_ << ", ";
		}
		else {
			os << "N/A" << ", ";
		}

		os << "detect:";
		os << "[";
		for_each(dect.detected_.begin(), dect.detected_.end(), [&os](const Candidate & can){os << can << ", "; });
		os << "]";

		os << "}";

		return os;
	}

	ofstream& Detection::toBinary(ofstream& fs) const{
		auto tm = static_cast<int>(time_);
		fs.write(reinterpret_cast<char*>(&tm), sizeof tm);
		
		WindVector wv;
		if (wv_) {
			wv = *wv_;
		}
		wv.toBinary(fs);

		auto num = static_cast<int>(detected_.size());
		fs.write(reinterpret_cast<char*>(&num), sizeof num);
		for_each(detected_.begin(), detected_.end(), [&fs](const Candidate & can){can.toBinary(fs); });

		return fs;
	}
}