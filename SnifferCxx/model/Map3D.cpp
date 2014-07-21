//
//  Map3D.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Map3D.h"

namespace Model {
	using namespace std;

	typedef map_t::extent_range erange;

	Map3D::Map3D(const Coordinate & startIndex, const Coordinate & boundary, unit_t unit)
		:map_t(boost::extents[erange(startIndex[0], startIndex[0] + boundary[0])][erange(startIndex[1], startIndex[1] + boundary[1])][erange(startIndex[2], startIndex[2] + boundary[2])]),
		unit_(unit) {

	}

	Map3D::Map3D(size_t length, size_t width, size_t height, unit_t unit)
		: map_t(boost::extents[length][width][height]),
		unit_(unit) {

	}

	unit_t Map3D::getUnit() const {
		return unit_;
	}

	const map_t::size_type * Map3D::getBoundary() const{
		return shape();
	}

	const map_t::index * Map3D::getStartIndex() const {
		return index_bases();
	}

	//************************************
	// Method:    insideMap : check if a position is in the map area or under the ground or out of boundary
	// FullName:  Model::Map3D::insideMap
	// Access:    public 
	// Returns:   boost::tribool : true->in the 3D map; false->out of boundary; indeterminate->under the groud.
	// Qualifier: const
	// Parameter: const Coordinate & pos : unit = cell index
	//************************************
	boost::tribool Map3D::insideMap(const Coordinate &pos) const{
		using namespace boost;

		auto start_pos = getStartIndex();
		auto boundary = getBoundary();

		bool in2D = start_pos[0] <= pos[0] && pos[0] < start_pos[0] + (int)boundary[0] && start_pos[1] <= pos[1] && pos[1] < start_pos[1] + (int)boundary[1];
		bool inHeight = (start_pos[2] <= pos[2]) && (pos[2] < start_pos[2] + (int)boundary[2]);
		bool underHeight = pos[2] < start_pos[2];

		if (in2D && underHeight)
		{
			return tribool(indeterminate);
		}

		return in2D && inHeight;
	}

	bool Map3D::updateCell(const Cell &cell) {
		(*this)(cell.getCoordinate()) = cell;

		return true;
	}

	Cell Map3D::getCell(const Coordinate & pos) const {
		return (*this)(pos);
	}

	//************************************
	// Method:    calcPosition
	// FullName:  Model::Map3D::calcPosition : calculate particle destination position after moving accorindg to the wind vecotr
	// Access:    public 
	// Returns:   Model::Coordinate
	// Qualifier: const
	// Parameter: const Coordinate & pos : start position, unit = cell index
	// Parameter: const WindVector & wv : wind vector, unit = meter / iteration
	//************************************
	Coordinate Map3D::calcPosition(const Coordinate & pos, const WindVector & wv) const {
		return pos + (wv / unit_);
	}

	//************************************
	// Method:    calcCollisionByEndCell : only check the end position cell for performance issue
	// FullName:  Model::Map3D::calcCollisionByEndCell
	// Access:    public 
	// Returns:   shared_ptr<Cell> : end cell if end position is in the 3d map and it is a air cell, 
	//								 return start position cell if it hit on building or ground,
	//								 nullptr if end position is out of boundary
	// Qualifier:
	// Parameter: const Coordinate & startPos : start position, unit = cell index
	// Parameter: const Coordinate & endPos : ideal end position without care about collision, unit = cell index.
	//************************************
	shared_ptr<Cell> Map3D::calcCollisionByEndCell(const Coordinate & startPos, const Coordinate & endPos) const {
		auto pos_ret = insideMap(endPos);

		if (pos_ret) { // end pos is still in the map .
			auto endCell = getCell(endPos);
			if (endCell.isAirCell()) {//and it is a air cell
				return make_shared<Cell>(endCell);
			}
		}
		else if (!pos_ret) {// end pos is out of the boundary
			return nullptr;
		}


		return make_shared<Cell>(getCell(startPos)); //end pos hit on building or ground
	}

	//************************************
	// Method:    calcStep : calculate a step stride make star position move one step towards to destination position.
	// FullName:  Model::Map3D::calcStep 
	// Access:    private 
	// Returns:   Model::Coordinate : the result step, [0,0,0] means startPos already reach the destination.
	// Qualifier:
	// Parameter: const Coordinate & curPos : unit = cell index
	// Parameter: const Coordinate & dstPos : unit = cell index
	//************************************
	Coordinate Map3D::calcStep(const Coordinate & curPos, const Coordinate & dstPos)  const {
		Coordinate ret;
		transform(curPos.begin(), curPos.end(), dstPos.begin(), ret.begin(),
			[](coord_item_t it1, coord_item_t it2) {
			if (it1 < it2){
				return 1;
			}
			else if (it1 > it2) {
				return -1;
			}
			else {
				return 0;
			}
		});
		return ret;
	}

	//************************************
	// Method:    calcCollisionByFullPath : check all the cells form start pos to end pos for any collision
	// FullName:  Model::Map3D::calcCollisionByFullPath
	// Access:    public 
	// Returns:   shared_ptr<Cell> : end cell if movement reach the end position without any collision and it is still in the boundary
	//								 return the previous cell if the movement hit on building or ground,
	//								 nullptr if the movement is out of boundary
	// Qualifier:
	// Parameter: const Coordinate & startPos : start position, unit = cell index
	// Parameter: const Coordinate & endPos : ideal end position without care about collision, unit = cell index.
	//************************************
	shared_ptr<Cell> Map3D::calcCollisionByFullPath(const Coordinate & startPos, const Coordinate & endPos) const {
		auto curPos = startPos;

		while (curPos != endPos) {
			auto nextPos = curPos + calcStep(curPos, endPos);

			auto next_ret = insideMap(nextPos);
			if (!next_ret) { // end pos is out of boundary
				return nullptr;
			}
			else if (indeterminate(next_ret)) { //end pos is hit on ground
				return make_shared<Cell>(getCell(curPos));
			}

			auto nextCell = getCell(nextPos);
			if (!nextCell.isAirCell()) { //end pos is hit on building
				return make_shared<Cell>(getCell(curPos));
			}

			curPos = nextPos;
		}

		return make_shared<Cell>(getCell(curPos));
	}
}