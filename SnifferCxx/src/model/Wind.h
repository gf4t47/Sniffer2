//
//  Wind.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Wind__
#define __Sniffer_Cxx__Wind__

#include <iostream>
#include "WindVector.h"

namespace Model {
    class Wind {
    public:
        Wind();
        Wind(WindVector & wind, WindVector & potential);
        
        WindVector getWind();
        
    private:
        WindVector wind_;
        WindVector potential_;
    };
}

#endif /* defined(__Sniffer_Cxx__Wind__) */
