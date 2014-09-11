#include "Hypotheses.h"
#include <algorithm>
#include <fstream>
#include "../support/MyLog.h"

namespace Model {
	using namespace std;
	using namespace Support;

//	unique_ptr<MyLog> Hypotheses::lg_(make_unique<MyLog>());
    unique_ptr<MyLog> Hypotheses::lg_(new MyLog());

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

	ofstream& Hypotheses::toBinary(ofstream& fs) const {
		BOOST_LOG_SEV(*lg_, severity_level::detail) << "START HYPS:";

		auto num = static_cast<int>(size());
		fs.write(reinterpret_cast<char*>(&num), sizeof num);
		BOOST_LOG_SEV(*lg_, severity_level::detail) << "hyp num = " << num;

		for_each(begin(), end(), [&fs](const Hypothesis & hyp){hyp.toBinary(fs); });

		BOOST_LOG_SEV(*lg_, severity_level::detail) << "END HYPS:";

		return fs;
	}

}