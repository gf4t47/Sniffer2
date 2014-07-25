//
//  Cells.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Cells.h"
#include <sstream>

namespace Model {
	using namespace std;

	shared_ptr<Cell> Cells::getCell(const Coordinate & pos) const {
		auto find_ret = find(pos);
		if (find_ret == this->end())
		{
			return nullptr;
		}

		return make_shared<Cell>(find_ret->second);
	}

	shared_ptr<Cell> Cells::getCell(coord_item_t x, coord_item_t y, coord_item_t z) const {
		Coordinate coord(x, y, z);
		return getCell(coord);
	}

	bool Cells::updateCell(const Cell & cell) {
		(*this)[cell.getCoordinate()] = cell;
		return true;
	}

	//************************************
	// Method:    mergeCellsByAddMethane : merge two set of cells by add the methane in the same location.
	// FullName:  Model::Cells::mergeCellsByAddMethane
	// Access:    public 
	// Returns:   bool : true merge successfully, otherwise false
	// Qualifier:
	// Parameter: const Cells & cells
	//************************************
	bool Cells::mergeCellsByAddMethane(const Cells & cells) {
		for (auto oth_entry : cells) {
			auto find_ret = find(oth_entry.first);
			if (find_ret == end()) {
				updateCell(oth_entry.second);
			}
			else {
				if (find_ret->second == oth_entry.second)
				{
					auto original_methane = find_ret->second.getMethane().getParticleNum();
					auto new_methane = oth_entry.second.getMethane().getParticleNum();
					find_ret->second.setMethaneConcentration(original_methane + new_methane);
				}
				else {
					ostringstream ostr;
					ostr << "two cells to be merged are not same: " << endl; 
					ostr << "cell1 = " << find_ret->second << endl;
					ostr << "cell2 = " << oth_entry.second << endl;

					throw invalid_argument(ostr.str());
				}
			}
		}

		return true;
	}
}