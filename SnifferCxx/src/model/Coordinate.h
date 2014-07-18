//
//  Coordinate.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Coordinate__
#define __Sniffer_Cxx__Coordinate__

#include <iostream>
#include <array>

namespace Model {
    typedef std::array<int, 3> coord_t;
    
    class Coordinate : public coord_t {
    };
}

#endif /* defined(__Sniffer_Cxx__Coordinate__) */
