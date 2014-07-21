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
		virtual ~Hypothesis();

		const std::vector<Leak> & getLeaks() const;
		std::shared_ptr<Cells> getMethaneCells() const;

	private:
		std::vector<Leak> leaks_;
		std::shared_ptr<Cells> methane_cells_; //all the methane under current hypothesis in current time
		double probability_;

	};
}

