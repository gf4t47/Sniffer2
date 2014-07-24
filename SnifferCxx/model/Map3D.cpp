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
    
    const size_t default_potential_step = 3;
    const wv_item_t default_wind_norm = 1.618;

	MapBuilder::MapBuilder(coord_item_t length, coord_item_t width, coord_item_t height, unit_t unit) 
		:boundary_(length, width, height),
		unit_(unit),
        potentialStep_(default_potential_step) {

	}

	MapBuilder::MapBuilder(const Coordinate & boundary, unit_t unit)
		: boundary_(boundary),
		unit_(unit),
        potentialStep_(default_potential_step) {

	}

	MapBuilder * MapBuilder::setStartIndex(const Coordinate & startIndex) {
		startIndex_ = startIndex;
		return this;
	}

	MapBuilder * MapBuilder::setWind(const WindVector & wind) {
		wind_ = wind;
		return this;
	}
    
    MapBuilder * MapBuilder::setLocalPotential(coord_item_t step) {
        potentialStep_ = step;
        return this;
    }

	MapBuilder * MapBuilder::setBuildings(const std::vector<stBuilding> & buildings) {
		buildings_ = buildings;
		return this;
	}

	shared_ptr<Map3D> MapBuilder::build() {
		shared_ptr<Map3D> map;
		if (startIndex_) {
			map.reset(new Map3D(*startIndex_, boundary_, unit_));
		}
		else {
			map.reset(new Map3D(boundary_[0], boundary_[1], boundary_[2], unit_));
		}
        
        if (wind_)
		{
			map->updateWind(*wind_);
		}

		if (buildings_)
		{
			for (auto bld : *buildings_)
			{
				map->AddBuilding(bld, potentialStep_, wind_);
			}
		}

		return map;
	}

	Map3D::Map3D(const Coordinate & startIndex, const Coordinate & boundary, unit_t unit)
		:map_t(boost::extents[erange(startIndex[0], startIndex[0] + boundary[0])][erange(startIndex[1], startIndex[1] + boundary[1])][erange(startIndex[2], startIndex[2] + boundary[2])]),
		unit_(unit) {

	}

	Map3D::Map3D(size_t length, size_t width, size_t height, unit_t unit)
		: map_t(boost::extents[length][width][height]),
		unit_(unit) {

	}

	shared_ptr<vector<Coordinate>> Map3D::AddBuilding(const stBuilding & bld, coord_item_t potentialStep, boost::optional<WindVector> wind) {
		auto ret_vec = make_shared<vector<Coordinate>>();
		auto location = bld.location_;
		auto boudary = bld.boundary_;
        auto wind_norm = default_wind_norm;
        if (wind) {
            wind_norm = wind->calcNorm();
        }
		for (auto l = location[0]; l < location[0] + boudary[0]; l++) {
			for (auto w = location[1]; w < location[1] + boudary[1]; w++) {
				for (auto h = location[2]; h < location[2] + boudary[2]; h++) {
					Coordinate coord(l, w, h);
					if (insideMap(coord)) {
                        (*this)(coord).setCellTag(CellTag::Building);
						calcLocalPotential(coord, potentialStep, wind_norm);
						ret_vec->push_back(coord);
					}
				}
			}
		}

		return ret_vec;
	}
    
    void Map3D::calcLocalPotential(const Coordinate & local_coord, coord_item_t step, wv_item_t expected_norm) {
        for (auto l = local_coord[0] - step; l <= local_coord[0] + step; l++) {
            for (auto w = local_coord[1] - step; w <= local_coord[1] + step; w++) {
                for (auto h = local_coord[2] - step; h <= local_coord[2] + step; h++) {
                    Coordinate remote_coord(l, w, h);
                    if (remote_coord != local_coord && insideMap(remote_coord)) {
                        auto cell = getCell(remote_coord);
                        if (cell.isAirCell()) {
                            auto vector = remote_coord - local_coord;
                            auto potential = vector / (vector.calcNorm() / expected_norm);
                            (*this)(remote_coord).setPotential(potential);
                        }
                    }
                }
            }
        }
    }

	void Map3D::updateWind(const WindVector & wind) {
        boost::multi_array_ref<Cell, 1> map_ref(this->data(), boost::extents[this->num_elements()]);
        for_each(map_ref.begin(), map_ref.end(), [&wind](Cell & cell){cell.setWindVector(wind);});

	}
    
    bool Map3D::updateCell(const Cell &cell) {
		(*this)(cell.getCoordinate()) = cell;
        
		return true;
	}
    
	Cell Map3D::getCell(const Coordinate & pos) const {
		return (*this)(pos);
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

	bool Map3D::isAirCell(const Coordinate & pos) const {
		return (*this)(pos).isAirCell();
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
			if (!next_ret) { // next pos is out of boundary
				return nullptr;
			}
			else if (indeterminate(next_ret)) { //next pos is hit on ground
				return make_shared<Cell>(getCell(curPos));
			}

			auto nextCell = getCell(nextPos);
			if (!nextCell.isAirCell()) { //next pos is hit on building
				return make_shared<Cell>(getCell(curPos));
			}

			curPos = nextPos;
		}

		return make_shared<Cell>(getCell(curPos));
	}
}