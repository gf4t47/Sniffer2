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
#include "Cell.h"

namespace Support {
	class MyLog;
}

namespace Initializer {
    class MapBuilder;
}

namespace Model{
	typedef boost::multi_array<Cell, 3> map_t;

	class Map3D : public map_t{
	public:
		unit_t getUnit() const;

		bool isAirCell(const Coordinate & pos) const;
//        bool hasMethane(const Coordinate & pos) const;
//        mtn_t getMethane(const Coordinate & pos) const;
		boost::tribool insideMap(const Coordinate & pos) const;
		const Cell & getCell(const Coordinate & pos) const;
		bool updateCell(const Cell & cell);
        const map_t::size_type * getBoundary() const;
		const map_t::index * getStartIndex() const;


		std::tuple<Coordinate, WindVector> calcPosition(const Coordinate & pos, const WindVector & wv) const;
		std::shared_ptr<Cell> calcCollisionByFullPath(const Coordinate & startPos, const Coordinate & endPos) const;
		std::shared_ptr<Cell> calcCollisionByEndCell(const Coordinate & startPos, const Coordinate & endPos) const;

		void updateWind(const WindVector & wind) const;

		Coordinate locateIndex(const WindVector & real_coord) const;

		void setOrigin(const std::pair<Coordinate, WindVector> & origin);

		friend class Initializer::MapBuilder;
		std::ofstream& toBinary(std::ofstream& fs) const;

	protected:
        void initCell();

	private:
		Map3D(size_t length, size_t width, size_t height, unit_t unit);
		Map3D(const Coordinate & startIndex, const Coordinate & boundary, unit_t unit);
		Map3D(size_t length, size_t width, size_t height, unit_t unit, const WindVector & wv);
		Map3D(const Coordinate & startIndex, const Coordinate & boundary, unit_t unit, const WindVector & wv);
		Coordinate calcStep(const Coordinate & curPos, const Coordinate & dstPos) const;

		void calcLocalPotential(const Coordinate & local_coord, coord_item_t step, wv_item_t expected_norm);
		std::shared_ptr<std::vector<Coordinate>> AddBuilding(const Coordinate & location, const Coordinate & boundary, coord_item_t potentialStep, wv_item_t wind_norm);

	private:
		unit_t unit_;
		std::pair<Coordinate, WindVector> origin_;
		const std::unique_ptr<WindVector> wind_;
		static std::unique_ptr<Support::MyLog> lg_;
	};
}

#endif /* defined(__Sniffer_Cxx__Map3D__) */
