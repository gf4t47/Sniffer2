//
//  Cell.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Cell.h"

namespace Model {
    Cell::Cell()
    :coord_(Coordinate()),
    wind_(Wind()),
    mtn_(Methane()),
    tag_(CellTag::Air) {
        
    }
    
    Cell::Cell(Coordinate & coord, CellTag tag, Methane & mtn, Wind & wind)
    :coord_(coord),
    wind_(wind),
    mtn_(mtn),
    tag_(tag) {
        
    }
    
    Wind & Cell::getWind() {
        return wind_;
    }
    
    Methane & Cell::getMethane() {
        return mtn_;
    }
    
    Coordinate Cell::getCoordinate() {
        return coord_;
    }
    
    CellTag Cell::getTag() {
        return tag_;
    }
    
    bool Cell::isAirCell() {
        return getTag() == CellTag::Air;
    }
}