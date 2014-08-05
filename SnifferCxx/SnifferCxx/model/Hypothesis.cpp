#include "Hypothesis.h"
#include "Cells.h"
#include <thread>

namespace Model {
	using namespace std;
    
    Hypothesis::Hypothesis(const Hypothesis & oth)
    :leaks_(oth.leaks_),
    probability_his_(oth.probability_his_),
    cells_update_his_(oth.cells_update_his_) {
        
    }

	Hypothesis::Hypothesis(const vector<Leak> & leaks, double probability)
		:leaks_(leaks) {
            addProbability(probability);
	}

    Hypothesis::Hypothesis(const vector<Leak> & leaks, const vector<pair<int, double>> & prob_his, const shared_ptr<Cells> initial_cells)
    :leaks_(leaks),
    probability_his_(prob_his) {
        if (initial_cells) {
            cells_update_his_.push_back(initial_cells);
        }
	}

	Hypothesis::~Hypothesis() {
	}

	const vector<Leak> & Hypothesis::getLeaks() const {
		return leaks_;
	}

    void Hypothesis::addCellsHistory(const shared_ptr<Cells> cells) {
        lock_guard<mutex> lock(cells_his_mutex_);
        
        cells_update_his_.push_back(cells);
    }
    
    const shared_ptr<Cells> Hypothesis::getMethaneCells() const {
//        lock_guard<mutex> lock(cells_his_mutex_);
        
        if (cells_update_his_.size() > 0) {
            return cells_update_his_.back();
        }
        
        return nullptr;
    }

	const std::vector<std::shared_ptr<Cells>> & Hypothesis::getCelllsHistory() const{
        
		return cells_update_his_;
	}
    
    int Hypothesis::getCurrentCellsHisIndex() const{
//        lock_guard<mutex> lock(cells_his_mutex_);
        
        return (int)cells_update_his_.size() - 1;
    }
    
    const vector<pair<int, double>> & Hypothesis::getProbabilityHistory() const {
        return probability_his_;
    }
    
    double Hypothesis::getProbability() const {
        if (probability_his_.size() > 0) {
            return probability_his_.back().second;
        }
        
        return 0.0;
    }
    
    void Hypothesis::addProbability(double val) {
        probability_his_.push_back(make_pair(getCurrentCellsHisIndex(), val));
    }
}