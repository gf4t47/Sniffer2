#include "Hypothesis.h"
#include "Cells.h"

namespace Model {
	using namespace std;

	Hypothesis::Hypothesis(const vector<Leak> & leaks, double probability)
		:leaks_(leaks),
		probability_(probability),
		methane_cells_(make_shared<Cells>()){

	}


	Hypothesis::~Hypothesis()
	{
	}

	const vector<Leak> & Hypothesis::getLeaks() const {
		return leaks_;
	}

	shared_ptr<Cells> Hypothesis::getMethaneCells() const {
		return methane_cells_;
	}
}