#pragma once

#include <vector>
#include "Coordinate.h"
#include "Methane.h"

namespace Model {
	class Cells;

	struct Leak {
		Coordinate location_;
		mtn_t concentration_;
	};

	class Hypothesis
	{
	public:
		Hypothesis(const std::vector<Leak> & leaks, double probability);
        Hypothesis(const std::vector<Leak> & leaks, double probability, const std::shared_ptr<Cells> cells);
		virtual ~Hypothesis();

		const std::vector<Leak> & getLeaks() const;
        double getProbability() const;
        bool setProbability(double val);
		std::shared_ptr<Cells> getMethaneCells() const;

	private:
		std::vector<Leak> leaks_;
		std::shared_ptr<Cells> methane_cells_;
		double probability_;

	};
}

