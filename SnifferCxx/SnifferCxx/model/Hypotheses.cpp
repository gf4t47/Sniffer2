#include "Hypotheses.h"
#include <algorithm>

namespace Model {

	Hypotheses::Hypotheses()
	:Asyn_Deduce_(true) {
	}


	Hypotheses::~Hypotheses() {
	}

	const Hypothesis & Hypotheses::getMaxProbHyp() {
		auto max = std::max_element(this->begin(), this->end(),
			[](const Hypothesis & left, const Hypothesis & right) {
			if (left.getProbability() < right.getProbability()) {
				return true;
			}
			else {
				return false;
			}
		});
		return *max;
	}

	bool Hypotheses::getAsynFlag() {
		return Asyn_Deduce_;
	}

	void Hypotheses::setAsynFlag(bool val) {
		Asyn_Deduce_ = val;
	}

}