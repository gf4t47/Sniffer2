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
#include <boost/functional/hash.hpp>
#include "WindVector.h"

namespace Model {
    typedef std::array<int, 3> coord_t;
    
    class Coordinate : public coord_t {
    public:
        Coordinate();
        Coordinate(int x, int y, int z);
        
        WindVector operator+ (const WindVector & oth) const;
        
        friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord);
        
        struct CoordHasher
        {
            std::size_t operator()(const Coordinate & key) const
            {
                using boost::hash_value;
                using boost::hash_combine;
                
                std::size_t seed = 0;
                
                hash_combine(seed, hash_value(key[0]));
                hash_combine(seed, hash_value(key[1]));
                hash_combine(seed, hash_value(key[2]));
                
                return seed;
            }
        };
    };
}

#endif /* defined(__Sniffer_Cxx__Coordinate__) */
