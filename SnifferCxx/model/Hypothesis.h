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
        Hypothesis(const std::vector<Leak> & leaks, double probability, const std::shared_ptr<Cells> initial_cells);
		virtual ~Hypothesis();

		const std::vector<Leak> & getLeaks() const;
        double getProbability() const;
        bool setProbability(double val);
        
        void addCellsHistory(const std::shared_ptr<Cells> cells);
        const std::shared_ptr<Cells> getMethaneCells() const;

	private:
        double probability_;
		std::vector<Leak> leaks_;
        std::vector<std::shared_ptr<Cells>> cells_update_his_;

	};
}

