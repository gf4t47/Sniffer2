#pragma once

#include <vector>
#include <mutex>
#include "Coordinate.h"
#include "Methane.h"

namespace Model {
	class Cells;

	struct Leak {
		Coordinate location_;
		mtn_t concentration_; //concentration in a detection object, information gain score for a candidate object... yeah! they share the same struct.
        
        Leak(const Coordinate & loc, const mtn_t & conc)
        :location_(loc),
        concentration_(conc) {
            
        }
        
        Leak()
        :location_(Coordinate()),
        concentration_(mtn_t()) {
            
        }
	};

	class Hypothesis
	{
	public:
        Hypothesis(const Hypothesis & oth);
		Hypothesis(const std::vector<Leak> & leaks, double probability);
        Hypothesis(const std::vector<Leak> & leaks, double probability, const std::shared_ptr<Cells> initial_cells);
		virtual ~Hypothesis();

		const std::vector<Leak> & getLeaks() const;
        
        double getProbability() const;
        void setProbability(double val);
        
        void addCellsHistory(const std::shared_ptr<Cells> cells);
        const std::shared_ptr<Cells> getMethaneCells() const;
		const std::vector<const std::shared_ptr<Cells>> & getCelllsHistory() const;
        
        static const Hypothesis & getMaxProbHyp(const std::vector<Hypothesis> & hyps);
        
    private:
        int getCurrentCellsHisIndex() const;

	private:
        std::vector<Leak> leaks_;
        double probability_;
        std::vector<const std::shared_ptr<Cells>> cells_update_his_;
        
        mutable std::mutex cells_his_mutex_;
	};
}

