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
#include <memory>
#include "Cell.h"
#include "Coordinate.h"

namespace Model{
    typedef size_t unit_t;
    typedef boost::multi_array<Cell, 3> map_t;
    
    class Map3D : public map_t{
    public:
        Map3D(Coordinate & startIndex, Coordinate & range, unit_t unit);
        
        unit_t getUnit();
        
        bool underGround(Coordinate & pos);
        
    protected:
        std::shared_ptr<Coordinate> getStartIndex();
        std::shared_ptr<Coordinate> getBoundary();
        
    private:
        unit_t unit_;
    };
}

#endif /* defined(__Sniffer_Cxx__Map3D__) */
