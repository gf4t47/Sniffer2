//
//  ForwardChecking.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "ForwardChecking.h"
#include "../model/Hypotheses.h"
#include "../model/Cells.h"
#include "../model/Map3D.h"
#include "../model/Candidate.h"

namespace Forward
{
	using namespace std;
	using namespace Model;

	ForwardChecking::ForwardChecking(range_t kernnel_range, int iteration_per_sec)
		:gaussian_kernel_range_(kernnel_range),
		 iteration_per_sec_(iteration_per_sec)
	{
	}

	ForwardChecking::~ForwardChecking()
	{
	}

	range_t ForwardChecking::getKernelRange() const
	{
		return gaussian_kernel_range_;
	}

	int ForwardChecking::getIterationPerSecond() const
	{
		return iteration_per_sec_;
	}

	//************************************
	// Method:    Deduce : enter face for this algorithm class
	// FullName:  Forward::ForwardChecking::Deduce
	// Access:    public
	// Returns:   shared_ptr<Cells>
	// Qualifier: const
	// Parameter: const Hypothesis & hypothesis
	// Parameter: const Map3D & map
	// Parameter: size_t count
	//************************************
	shared_ptr<Cells> ForwardChecking::Deduce(Hypothesis& hypothesis, const Map3D& map, int time_count, bool keep_history) const
	{
		Cells leakCells; // more leaked methane cells added in each iteration.
		for (auto leak : hypothesis.getLeaks())
		{
			auto leakCell = map.getCell(leak.location_);
			leakCell.setMethane(Methane(leak.concentration_));
			leakCells.updateCell(leakCell);
		}

		auto methane_cells = hypothesis.getMethaneCells();
		auto ret_cells = make_shared<Cells>();
		if (methane_cells)
		{
			ret_cells = make_shared<Cells>(*methane_cells); //copy constructor here to storage the history of methane cells.
		}

		for (size_t i = 0; i < time_count; i++)
		{
			ret_cells->mergeCellsByAddMethane(leakCells);
			ret_cells = calcEnds(*ret_cells, map);
			if (keep_history && i < time_count - 1 && i % getIterationPerSecond() == 0)
			{
				hypothesis.addCellsToHistory(ret_cells);
			}
		}

		return ret_cells;
	}

	shared_ptr<Hypotheses> ForwardChecking::UpdateMethane(Hypotheses& hyps, const Map3D& map, int time_count) const
	{
		auto ret_hyps = make_shared<Hypotheses>();

		for (auto& hyp : hyps)
		{
			auto newCells = Deduce(hyp, map, time_count, true);
			Hypothesis newHyp(hyp.getLeaks(), hyp.getProbability(), newCells);
			ret_hyps->push_back(newHyp);
		}

		return ret_hyps;
	}

	void ForwardChecking::update_once(Hypotheses& hyps, const Map3D& map) const
	{
		for (auto& hyp : hyps)
		{
			auto newCells = Deduce(hyp, map, 1, true);
			hyp.addCellsToHistory(newCells);
		}
	}


	//************************************
	// Method:    initHypotheses
	// FullName:  Forward::ForwardChecking::initHypotheses, initialize methane to steady stage.
	// Access:    public 
	// Returns:   std::shared_ptr<Model::Hypotheses>
	// Qualifier: const
	// Parameter: Model::Hypotheses & hyps
	// Parameter: const Model::Map3D & map
	// Parameter: int time_count
	//************************************
	shared_ptr<Hypotheses> ForwardChecking::initHypotheses(Hypotheses& hyps, const Map3D& map, int time_count) const
	{
		auto ret_hyps = make_shared<Hypotheses>();

		for (auto& hyp : hyps)
		{
			auto newCells = Deduce(hyp, map, time_count, false);
			Hypothesis newHyp(hyp.getLeaks(), hyp.getProbability(), newCells);
			ret_hyps->push_back(newHyp);
		}

		return ret_hyps;
	}
}