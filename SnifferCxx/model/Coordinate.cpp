//
//  Coordinate.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Coordinate.h"

namespace Model {
    using namespace std;
    
    Coordinate::Coordinate()
    :coord_t{0,0,0} {
        
    }

    Coordinate::Coordinate(int x, int y, int z)
    :coord_t{x,y,z} {
        
    }
    
    WindVector Coordinate::operator+(const Model::WindVector &oth) const{
        WindVector ret;
        transform(oth.begin(), oth.end(), begin(), ret.begin(), [](double it1, int it2){return it1 + it2;});
        return ret;
    }
    
    ostream& operator<<(ostream& os, const Coordinate& coord)
    {
        os << "("<<coord[0] <<", "<<coord[1]<<", "<<coord[2]<<")";
        
        return os;
    }
}