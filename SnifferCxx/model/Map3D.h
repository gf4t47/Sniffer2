//
//  Map3D.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Map3D__
#define __Sniffer_Cxx__Map3D__

#include <iostream>

#include <iostream>
#include <boost/multi_array.hpp>
#include "Cell.h"
#include "Coordinate.h"

namespace Model{
    typedef size_t unit_t;
    typedef boost::multi_array<Cell, 3> map_t;
    
    class Map3D : public map_t{
    public:
        Map3D(size_t length, size_t width, size_t height, unit_t unit);
        Map3D(Coordinate & startIndex, Coordinate & boundary, unit_t unit);
        
        unit_t getUnit() const;
        
        bool underGround(Coordinate & pos) const;
        bool insideMap(Coordinate & pos) const;
        Cell getCell(Coordinate & pos) const;
        
        bool updateCell(Cell & cell);

		Coordinate & locatePosition(const WindVector & pos) const;
        
    protected:
        const size_t * getStartIndex() const;
        const map_t::index * getBoundary() const;
        
    private:
        unit_t unit_;
    };
}

#endif /* defined(__Sniffer_Cxx__Map3D__) */
