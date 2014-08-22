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
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace Model {
	class WindVector;

	typedef int coord_item_t;
	typedef std::array<coord_item_t, 3> coord_t;

	class Coordinate : public coord_t {
	public:
		Coordinate();
		Coordinate(coord_item_t x, coord_item_t y, coord_item_t z);
        
        double calcNorm() const;

		Coordinate operator+ (const Coordinate & rhs) const;
        Coordinate operator- (const Coordinate & rhs) const;
        WindVector operator/ (const double & norm) const;
		Coordinate & operator= (const coord_t & rhs);

		friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord);
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & (*this)[0];
            ar & (*this)[1];
            ar & (*this)[2];
        }
	};

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
}

#endif /* defined(__Sniffer_Cxx__Coordinate__) */
