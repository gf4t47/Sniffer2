#pragma once

#include "Hypothesis.h"

namespace Model {

	class Hypotheses : public std::vector<Hypothesis>
	{
	public:
		Hypotheses();
		~Hypotheses();

		const Hypothesis & getMaxProbHyp();

		bool getAsynFlag();
		void setAsynFlag(bool val);

	private:
		bool Asyn_Deduce_;
	};

}

