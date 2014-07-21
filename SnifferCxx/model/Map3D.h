//
//  Map3D.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Map3D__
#define __Sniffer_Cxx__Map3D__

#include <boost/multi_array.hpp>
#include <boost/logic/tribool.hpp>
#include "Cell.h"

namespace Model{
	typedef boost::multi_array<Cell, 3> map_t;

	class Map3D : public map_t{
	public:
		Map3D(size_t length, size_t width, size_t height, unit_t unit);
		Map3D(const Coordinate & startIndex, const Coordinate & boundary, unit_t unit);

		unit_t getUnit() const;

		boost::tribool insideMap(const Coordinate & pos) const;
		Cell getCell(const Coordinate & pos) const;
		bool updateCell(const Cell & cell);

		Coordinate calcPosition(const Coordinate & pos, const WindVector & wv) const;
		std::shared_ptr<Cell> calcCollisionByFullPath(const Coordinate & startPos, const Coordinate & endPos) const;
		std::shared_ptr<Cell> calcCollisionByEndCell(const Coordinate & startPos, const Coordinate & endPos) const;

		const map_t::size_type * getBoundary() const;
		const map_t::index * getStartIndex() const;

	private:
		Coordinate calcStep(const Coordinate & curPos, const Coordinate & dstPos) const;

	private:
		unit_t unit_;
	};
}

#endif /* defined(__Sniffer_Cxx__Map3D__) */
