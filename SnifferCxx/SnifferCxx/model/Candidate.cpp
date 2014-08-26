#include "Candidate.h"

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
		os << "[";
		for_each(dect.detected_.begin(), dect.detected_.end(), [&os](const Candidate & can){os << can << ", "; });
		os << "]";
		os << "}";

		return os;
	}
}