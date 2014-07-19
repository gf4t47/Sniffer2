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
    
    Map3D::Map3D(Coordinate & startIndex, Coordinate & boundary, unit_t unit)
    :map_t(boost::extents[erange(startIndex[0], startIndex[0] + boundary[0])][erange(startIndex[1], startIndex[1] + boundary[1])][erange(startIndex[2], startIndex[2] + boundary[2])]),
    unit_(unit) {
        
    }
    
    Map3D::Map3D(size_t length, size_t width, size_t height, unit_t unit)
    :map_t(boost::extents[length][width][height]),
    unit_(unit) {
        
    }
    
    unit_t Map3D::getUnit() const {
        return unit_;
    }
    
    const size_t * Map3D::getStartIndex() const {
        return shape();
    }
    
    const map_t::index * Map3D::getBoundary() const {
        return index_bases();
    }
    
    bool Map3D::underGround(Coordinate &pos) const {
        auto start_pos = getStartIndex();
        auto boundary = getBoundary();
        
        return start_pos[0] <= pos[0] && pos[0] < start_pos[0] + boundary[0] && start_pos[1] <= pos[1] && pos[1] < start_pos[1] + boundary[1] && pos[2] < start_pos[2];
    }
    
    bool Map3D::insideMap(Coordinate &pos) const{
        auto start_pos = getStartIndex();
        auto boundary = getBoundary();
        
        return start_pos[0] <= pos[0] && pos[0] < start_pos[0] + boundary[0] && start_pos[1] <= pos[1] && pos[1] < start_pos[1] + boundary[1] && start_pos[2] <= pos[2] && pos[2] < start_pos[2] + boundary[2];
    }
    
    bool Map3D::updateCell(Cell &cell) {
        (*this)(cell.getCoordinate()) = cell;
        
        return true;
    }
    
    Cell Map3D::getCell(Coordinate & pos) const{
        return (*this)(pos);
    }
}