#include "Hypothesis.h"
#include "Cells.h"

namespace Model {
	using namespace std;

	Hypothesis::Hypothesis(const vector<Leak> & leaks, double probability)
		:leaks_(leaks),
		probability_(probability) {

	}

    Hypothesis::Hypothesis(const vector<Leak> & leaks, double probability, const shared_ptr<Cells> initial_cells)
    :leaks_(leaks),
    probability_(probability) {
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
        cells_update_his_.push_back(cells);
    }
    
    const shared_ptr<Cells> Hypothesis::getMethaneCells() const {
        if (cells_update_his_.size() > 0) {
            return cells_update_his_.back();
        }
        
        return nullptr;
    }
    
    double Hypothesis::getProbability() const {
        return probability_;
    }
    
    bool Hypothesis::setProbability(double val) {
        probability_ = val;
        return true;
    }
}