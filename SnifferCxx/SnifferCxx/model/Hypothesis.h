#pragma once

#include <vector>
//#include <mutex>
#include <memory>

namespace Model {
	class Cells;
	struct Candidate;

	class Hypothesis
	{
	public:
        Hypothesis(const Hypothesis & oth);
		Hypothesis(const std::vector<Candidate> & leaks, double probability);
        Hypothesis(const std::vector<Candidate> & leaks, double probability, const std::shared_ptr<Cells> initial_cells);
		virtual ~Hypothesis();

		const std::vector<Candidate> & getLeaks() const;
        
        double getProbability() const;
        void setProbability(double val);
        
        void addCellsToHistory(const std::shared_ptr<Cells> cells);
        const std::shared_ptr<Cells> getMethaneCells() const;
		const std::shared_ptr<Cells> popMethaneCells();
		const std::vector<const std::shared_ptr<Cells>> & getCelllsHistory() const;
        
    private:
        int getCurrentCellsHisIndex() const;

	private:
        std::vector<Candidate> leaks_;
        double probability_;
        std::vector<const std::shared_ptr<Cells>> cells_update_his_;
        
        //mutable std::mutex cells_his_mutex_;
	};
}

