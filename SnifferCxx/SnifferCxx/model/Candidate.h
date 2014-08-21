#pragma once

#include "Coordinate.h"
#include "TypeDef.h"

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
	};
}


