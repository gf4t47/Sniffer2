#pragma once

#include "Coordinate.h"
#include "WindVector.h"
#include <boost/optional.hpp>

namespace Model {
	struct Candidate {
		Coordinate location_;
		mtn_t concentration_; //concentration in a detection object, information gain score for a candidate object... yeah:( they share the same struct.

		Candidate(const Coordinate & loc, const mtn_t & conc)
			:location_(loc),
			concentration_(conc) {
		}

		Candidate()
			:location_(Coordinate()),
			concentration_(mtn_t()) {
		}

		friend std::ostream& operator<<(std::ostream& os, const Candidate & can);
		std::ofstream& toBinary(std::ofstream& fs) const;
	};

	struct Detection {
		int time_;
		boost::optional<Model::WindVector> wv_;
		std::vector<Candidate> detected_;

		friend std::ostream& operator<<(std::ostream& os, const Detection & dect);
		std::ofstream& toBinary(std::ofstream& fs) const;
	};

	struct AutoMovement {
		AutoMovement()
			:time_(0),
			distance_(0) {
		}

		AutoMovement(int time, Model::unit_t distance)
			:time_(time),
			distance_(distance) {
		}

		int time_;
		double threshold_;
		Model::unit_t distance_;
	};
}


