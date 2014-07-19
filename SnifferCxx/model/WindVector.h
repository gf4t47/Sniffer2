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
	class Coordinate;

	typedef double wv_item_t;
	typedef std::array<wv_item_t, 3> wv_t;

    class WindVector : public wv_t {
    public:
		WindVector();
		WindVector(wv_item_t x, wv_item_t y, wv_item_t z);
        WindVector operator+ (const WindVector & oth) const;
		WindVector operator+ (const Coordinate & oth) const;
        
        friend std::ostream& operator<<(std::ostream& os, const WindVector& wv);
    };
}

#endif /* defined(__Sniffer_Cxx__WindVector__) */
