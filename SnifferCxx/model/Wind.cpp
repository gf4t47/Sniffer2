//
//  Wind.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Wind.h"

namespace Model {
    using namespace std;
    
    Wind::Wind()
    :potential_(WindVector()),
    wind_(WindVector()) {
        
    }
    
    Wind::Wind(WindVector & wind, WindVector & potential)
    :potential_(potential),
    wind_(wind) {
        
    }
    
    WindVector Wind::getWindVector() const {
        return wind_ + potential_;
    }
    
    ostream& operator<<(ostream& os, const Wind& wind)
    {
        os << "{"<<wind.wind_ <<" + "<<wind.potential_<<"}";
        
        return os;
    }
}