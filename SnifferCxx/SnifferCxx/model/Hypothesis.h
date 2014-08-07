#pragma once

#include <vector>
#include <mutex>
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
        Hypothesis(const Hypothesis & oth);
		Hypothesis(const std::vector<Leak> & leaks, double probability);
        Hypothesis(const std::vector<Leak> & leaks, const std::vector<std::pair<int, double>> & prob_his, const std::shared_ptr<Cells> initial_cells);
		virtual ~Hypothesis();

		const std::vector<Leak> & getLeaks() const;
        
        double getProbability() const;
        double getProbabilityByIteration(int index) const;
        void addProbability(double val);
        const std::vector<std::pair<int, double>> & getProbabilityHistory() const;
        
        void addCellsHistory(const std::shared_ptr<Cells> cells);
        const std::shared_ptr<Cells> getMethaneCells() const;
		const std::vector<std::shared_ptr<Cells>> & getCelllsHistory() const;
        
    private:
        int getCurrentCellsHisIndex() const;

	private:
        std::vector<Leak> leaks_;
        std::vector<std::pair<int, double>> probability_his_;
        std::vector<std::shared_ptr<Cells>> cells_update_his_;
        mutable std::mutex cells_his_mutex_;
	};
}

