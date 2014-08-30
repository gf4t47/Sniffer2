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

	ofstream& operator<<(ofstream& fs, const Candidate& can) {
		fs << can.location_;
		fs << can.concentration_;
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

	ofstream& operator<<(ofstream& fs, const Detection& dect) {
		fs << dect.time_;
		if (dect.wv_) {
			fs << *dect.wv_;
		}
		else {
			fs << WindVector();
		}

		fs << static_cast<int>(dect.detected_.size());
		for_each(dect.detected_.begin(), dect.detected_.end(), [&fs](const Candidate & can){fs << can; });

		return fs;
	}
}