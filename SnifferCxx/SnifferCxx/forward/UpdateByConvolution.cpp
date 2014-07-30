#include "UpdateByConvolution.h"
#include "../model/Map3D.h"
#include "../math/GaussianBlur.h"

namespace Forward {
    using namespace std;
    using namespace Model;
    
	UpdateByConvolution::UpdateByConvolution(int blur_range)
        :UpdateByCell(blur_range) {

	}


	UpdateByConvolution::~UpdateByConvolution()	{

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
	shared_ptr<Cells> UpdateByConvolution::calcEnds(const Cell & cell, const Map3D & map) const {
		if (!cell.hasMethane()) {
			return make_shared<Cells>();
		}
        
        auto startPos = cell.getCoordinate();
        auto ideal_endPos =  map.calcPosition(startPos, cell.getWind().getCalcWind());
        auto endCell = calcEndcell(startPos, ideal_endPos, map, true);
        
        if(endCell) {
            return Math::GaussianBlur::blurCell(endCell->getCoordinate(), getBlurRange(), cell.getMethane().getParticleNum(), map);
        }
        
        return make_shared<Cells>();

	}

}
