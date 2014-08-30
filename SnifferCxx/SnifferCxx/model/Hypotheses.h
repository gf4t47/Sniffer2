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

		friend std::ofstream& operator<<(std::ofstream& fs, const Hypotheses& hyps);

	private:
		bool Asyn_Deduce_;
	};

}

