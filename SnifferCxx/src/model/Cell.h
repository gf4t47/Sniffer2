//
//  Cell.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Cell__
#define __Sniffer_Cxx__Cell__

#include <iostream>
#include "Wind.h"
#include "Methane.h"
#include "Coordinate.h"

namespace Model {
    enum class CellTag {
        Air,
        Ground,
        Building
    };
    
    class Cell {
    public:
        Cell();
        Cell(Coordinate & coord, CellTag tag, Methane & mtn, Wind & wind);
        
        Wind & getWind();
        Methane & getMethane();
        Coordinate getCoordinate();
        
        bool isAirCell();
        
    private:
        CellTag getTag();
        
    private:
        Coordinate coord_;
        Wind wind_;
        Methane mtn_;
        CellTag tag_;
    };
}

#endif /* defined(__Sniffer_Cxx__Cell__) */
