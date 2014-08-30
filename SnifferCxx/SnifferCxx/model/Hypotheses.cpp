#include "Hypotheses.h"
#include <algorithm>
#include <fstream>

namespace Model {
	using namespace std;

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

	ofstream& operator<<(ofstream& fs, const Hypotheses& hyps) {
		fs << static_cast<int>(hyps.size());
		for_each(hyps.begin(), hyps.end(), [&fs](const Hypothesis & hyp){fs << hyp; });

		return fs;
	}

}