//
//  WindVector.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__WindVector__
#define __Sniffer_Cxx__WindVector__

#include <iostream>
#include <array>

namespace Model {
    class WindVector : public std::array<double, 3> {
    public:
		WindVector();
		WindVector(double x, double y, double z);
        WindVector operator+ (const WindVector & oth);
    };
}

#endif /* defined(__Sniffer_Cxx__WindVector__) */
