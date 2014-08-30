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
		friend std::ofstream& operator<<(std::ofstream& fs, const Candidate & can);
	};

	struct Detection {
		int time_;
		boost::optional<Model::WindVector> wv_;
		std::vector<Candidate> detected_;

		friend std::ostream& operator<<(std::ostream& os, const Detection & dect);
		friend std::ofstream& operator<<(std::ofstream& fs, const Detection & dect);
	};

	struct AutoMovement {
		int time_;
		double threshold_;
		Model::unit_t distance_;
	};
}


