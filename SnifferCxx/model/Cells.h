//
//  Cells.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Cells__
#define __Sniffer_Cxx__Cells__

#include <iostream>
#include <unordered_map>
#include "Cell.h"

namespace Model{
    typedef std::unordered_map<Coordinate, Cell, Coordinate::CoordHasher> cells_t;
    class Cells : public cells_t{
        
    };
}

#endif /* defined(__Sniffer_Cxx__Cells__) */
