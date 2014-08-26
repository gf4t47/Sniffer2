//
//  Cells.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Cells__
#define __Sniffer_Cxx__Cells__

#include <unordered_map>
#include "Cell.h"

namespace Support {
	class MyLog;
}

namespace Model{
	typedef std::unordered_map<Coordinate, Cell, CoordHasher> cells_t;
	class Cells : public cells_t{
	public:
		std::shared_ptr<Cell> getCell(const Coordinate & pos) const;
		std::shared_ptr<Cell> getCell(coord_item_t x, coord_item_t y, coord_item_t z) const;
		bool updateCell(const Cell & cell);

		bool mergeCellsByAddMethane(const Cells & cells);

	private:
		static std::unique_ptr<Support::MyLog> lg_;
	};
}

#endif /* defined(__Sniffer_Cxx__Cells__) */
