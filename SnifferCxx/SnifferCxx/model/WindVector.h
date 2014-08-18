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
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "TypeDef.h"

namespace Model {
	class Coordinate;

	typedef double wv_item_t;
	typedef std::array<wv_item_t, 3> wv_t;

	class WindVector : public wv_t {
	public:
		WindVector();
		WindVector(wv_item_t x, wv_item_t y, wv_item_t z);
        
        wv_item_t calcNorm() const;
        
		WindVector operator+ (const WindVector & oth) const;
		Coordinate operator/ (const unit_t & unit) const;
		WindVector & operator= (const wv_t & rhs);

		friend std::ostream& operator<<(std::ostream& os, const WindVector& wv);
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & (*this)[0];
            ar & (*this)[1];
            ar & (*this)[2];
        }
	};
}

#endif /* defined(__Sniffer_Cxx__WindVector__) */
