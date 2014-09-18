#include "UpdateByConvolution.h"
#include "../model/Map3D.h"
#include "../math/GaussianBlur.h"
#include "../model/Cells.h"
#include "../model/Map3D.h"

namespace Forward
{
	using namespace std;
	using namespace Model;

	const int blur_concentration_threshold = 7;

	UpdateByConvolution::UpdateByConvolution(range_t kernel_range, int iteration_per_sec)
		:UpdateByCell(kernel_range, iteration_per_sec)
	{
	}


	UpdateByConvolution::~UpdateByConvolution()
	{
	}

	//************************************
	// Method:    calcEnds : calculate the methane distribution started from one cell to multiple cells
	// FullName:  Forward::UpdateByConvolution::calcEnds
	// Access:    protected
	// Returns:   shared_ptr<Cells> : all the cells has methane after distribution
	// Qualifier: const
	// Parameter: const Cell & cell : methane starting cell
	// Parameter: const Map3D & map
	//************************************
	shared_ptr<Cells> UpdateByConvolution::calcEnds(const Cell& cell, const Map3D& map) const
	{
		if (!cell.hasMethane())
		{
			return make_shared<Cells>();
		}

		auto ret_cells = make_shared<Cells>();

		if (cell.getMethane().getParitcles() > blur_concentration_threshold)
		{
			auto wv_per_iteration = cell.getWind().getCalcWind() * (1.0 / static_cast<double>(getIterationPerSecond()));
			auto ideal_end_pair = map.calcPosition(cell.getCoordinate(), wv_per_iteration + cell.getMethane().getPotential());
			auto endCell = calcEndcell(cell.getCoordinate(), get<0>(ideal_end_pair), map, true);
			if (endCell)
			{
				endCell->setMethane(Methane(cell.getMethane().getParitcles(), get<1>(ideal_end_pair)));
				ret_cells = Math::GaussianBlur::blurCell(*endCell, map, getKernelRange());
			}
		}
		else
		{
			ret_cells = UpdateByCell::calcEnds(cell, map);
		}

		return ret_cells;
	}
}