#pragma once

#include "Hypothesis.h"

namespace Model {

	class Hypotheses : public std::vector<Hypothesis>
	{
	public:
		Hypotheses();
		~Hypotheses();

		const Hypothesis & getMaxProbHyp();
	};

}

