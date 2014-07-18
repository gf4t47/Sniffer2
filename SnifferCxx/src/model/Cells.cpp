//
//  Cells.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Cells.h"

namespace Model {
    using namespace std;
    
    typedef cells_t::extent_range erange;
    
    Cells::Cells(Coordinate & startIndex, Coordinate & range, unit_t unit)
    :multi_array<Cell, 3>(boost::extents[erange(startIndex[0], startIndex[0] + range[0])][erange(startIndex[1], startIndex[1] + range[1])][erange(startIndex[2], startIndex[2] + range[2])]),
    unit_(unit) {
        
    }
    
    unit_t Cells::getUnit() {
        return unit_;
    }
    
    shared_ptr<Coordinate> Cells::getStartIndex() {
//        return make_shared<Coordinate>(shape());
        return nullptr;
    }
    
    shared_ptr<Coordinate> Cells::getBoundary() {
//        return make_shared<Coordinate>(index_bases());
        return nullptr;
    }
    
    bool Cells::underGround(Coordinate &pos) {
        auto start_pos = * getStartIndex();
        auto boundary = * getBoundary();
        
        return start_pos[0] <= pos[0] && pos[0] < start_pos[0] + boundary[0] && start_pos[1] <= pos[1] && pos[1] < start_pos[1] + boundary[1] && pos[2] < start_pos[2];
    }
}