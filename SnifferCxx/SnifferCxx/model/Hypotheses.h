#pragma once

#include "Hypothesis.h"

namespace Support {
	class MyLog;
}

namespace Model {

	class Hypotheses : public std::vector<Hypothesis>
	{
	public:
		Hypotheses();
		~Hypotheses();

		const Hypothesis & getMaxProbHyp();

		bool getAsynFlag();
		void setAsynFlag(bool val);

		std::ofstream& toBinary(std::ofstream& fs) const;

	private:
		bool Asyn_Deduce_;
		static std::unique_ptr<Support::MyLog> lg_;
	};

}

