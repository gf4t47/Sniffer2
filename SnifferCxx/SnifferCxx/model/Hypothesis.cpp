#include "Hypothesis.h"
#include "Cells.h"
#include "Candidate.h"
#include <fstream>
#include "../support/MyLog.h"

namespace Model
{
	using namespace std;
	using namespace Support;

	//	unique_ptr<MyLog> Hypothesis::lg_(make_unique<MyLog>());
	unique_ptr<MyLog> Hypothesis::lg_(new MyLog());

	Hypothesis::Hypothesis(const Hypothesis& oth)
		:leaks_(oth.leaks_),
		 probability_(oth.probability_),
		 cells_update_his_(oth.cells_update_his_)
	{
	}

	Hypothesis::Hypothesis(const vector<Candidate>& leaks, double probability)
		:leaks_(leaks),
		 probability_(probability)
	{
	}

	Hypothesis::Hypothesis(const vector<Candidate>& leaks, double probability, const shared_ptr<Cells> initial_cells)
		:leaks_(leaks),
		 probability_(probability)
	{
		if (initial_cells)
		{
			cells_update_his_.push_back(initial_cells);
		}
	}

	Hypothesis::~Hypothesis()
	{
	}

	const vector<Candidate>& Hypothesis::getLeaks() const
	{
		return leaks_;
	}

	void Hypothesis::addCellsToHistory(const shared_ptr<Cells> cells)
	{
		//lock_guard<mutex> lock(cells_his_mutex_);

		cells_update_his_.push_back(cells);
	}

	const shared_ptr<Cells> Hypothesis::getMethaneCells() const
	{
		//        lock_guard<mutex> lock(cells_his_mutex_);

		if (cells_update_his_.size() > 0)
		{
			return cells_update_his_.back();
		}

		return nullptr;
	}

	const shared_ptr<Cells> Hypothesis::popMethaneCells()
	{
		//        lock_guard<mutex> lock(cells_his_mutex_);

		if (cells_update_his_.size() > 0)
		{
			auto ret = cells_update_his_.back();
			cells_update_his_.pop_back();
			return ret;
		}

		return nullptr;
	}

	const vector<const shared_ptr<Cells>>& Hypothesis::getCelllsHistory() const
	{
		return cells_update_his_;
	}

	int Hypothesis::getCurrentCellsHisIndex() const
	{
		//        lock_guard<mutex> lock(cells_his_mutex_);

		return static_cast<int>(cells_update_his_.size()) - 1;
	}

	double Hypothesis::getProbability() const
	{
		return probability_;
	}

	void Hypothesis::setProbability(double val)
	{
		probability_ = val;
	}

	ofstream& Hypothesis::toBinary(ofstream& fs) const
	{
		BOOST_LOG_SEV(*lg_, severity_level::detail) << "HYP:";

		auto prob = getProbability();
		fs.write(reinterpret_cast<char*>(&prob), sizeof prob);
		BOOST_LOG_SEV(*lg_, severity_level::detail) << "prob=" << prob;

		auto leak_num = static_cast<int>(leaks_.size());
		fs.write(reinterpret_cast<char*>(&leak_num), sizeof leak_num);
		BOOST_LOG_SEV(*lg_, severity_level::detail) << "leak_num=" << leak_num;
		for_each(leaks_.begin(), leaks_.end(), [&fs](const Candidate& can)
		         {
			         BOOST_LOG_SEV(*lg_, severity_level::detail) << can;
			         can.toBinary(fs);
		         });

		auto his_num = static_cast<int>(cells_update_his_.size());
		fs.write(reinterpret_cast<char*>(&his_num), sizeof his_num);
		BOOST_LOG_SEV(*lg_, severity_level::detail) << "his_num=" << his_num;
		for_each(cells_update_his_.begin(), cells_update_his_.end(), [&fs](shared_ptr<Cells> cells)
		         {
			         cells->toBinary(fs);
		         });

		return fs;
	}
}