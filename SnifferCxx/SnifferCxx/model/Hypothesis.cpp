#include "Hypothesis.h"
#include "Cells.h"
#include "Candidate.h"
#include <fstream>

namespace Model {
	using namespace std;
    
    Hypothesis::Hypothesis(const Hypothesis & oth)
    :leaks_(oth.leaks_),
    probability_(oth.probability_),
    cells_update_his_(oth.cells_update_his_) {
        
    }

	Hypothesis::Hypothesis(const vector<Candidate> & leaks, double probability)
		:leaks_(leaks),
    probability_(probability) {
        
	}

    Hypothesis::Hypothesis(const vector<Candidate> & leaks, double probability, const shared_ptr<Cells> initial_cells)
    :leaks_(leaks),
    probability_(probability) {
        if (initial_cells) {
            cells_update_his_.push_back(initial_cells);
        }
	}

	Hypothesis::~Hypothesis() {
	}

	const vector<Candidate> & Hypothesis::getLeaks() const {
		return leaks_;
	}

    void Hypothesis::addCellsToHistory(const shared_ptr<Cells> cells) {
        //lock_guard<mutex> lock(cells_his_mutex_);
        
        cells_update_his_.push_back(cells);
    }
    
    const shared_ptr<Cells> Hypothesis::getMethaneCells() const {
//        lock_guard<mutex> lock(cells_his_mutex_);
        
        if (cells_update_his_.size() > 0) {
            return cells_update_his_.back();
        }
        
        return nullptr;
    }

	const shared_ptr<Cells> Hypothesis::popMethaneCells() {
		//        lock_guard<mutex> lock(cells_his_mutex_);

		if (cells_update_his_.size() > 0) {
			auto ret = cells_update_his_.back();
			cells_update_his_.pop_back();
			return ret;
		}

		return nullptr;
	}

	const std::vector<const std::shared_ptr<Cells>> & Hypothesis::getCelllsHistory() const{
        
		return cells_update_his_;
	}
    
    int Hypothesis::getCurrentCellsHisIndex() const{
//        lock_guard<mutex> lock(cells_his_mutex_);
        
        return (int)cells_update_his_.size() - 1;
    }
    
    double Hypothesis::getProbability() const {
        return probability_;
    }
    
	void Hypothesis::setProbability(double val) {
		probability_ = val;
	}

	ofstream& operator<<(ofstream& fs, const Hypothesis& hyp) {
		fs << hyp.getProbability();

		auto const & leaks = hyp.getLeaks();
		fs << static_cast<int>(leaks.size());
		for_each(leaks.begin(), leaks.end(), [&fs](const Candidate& can){fs << can; });

		auto const & cells_his = hyp.getCelllsHistory();
		fs << static_cast<int>(cells_his.size());
		for_each(cells_his.begin(), cells_his.end(), [&fs](shared_ptr<Cells> cells){fs << *cells; });

		return fs;
	}
}