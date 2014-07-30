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
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace Model {
	class Wind {
	public:
		Wind();
		Wind(const WindVector & wind);
		Wind(const WindVector & wind, const WindVector & potential);

		WindVector getCalcWind() const;
        WindVector getPotential() const;
		WindVector getWV() const;
        
        bool setWindVector(const WindVector & vec);
        bool setPotential(const WindVector & potential);
        
		bool operator== (const Wind & oth) const;
		friend std::ostream& operator<<(std::ostream& os, const Wind& wind);
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & wind_;
            ar & potential_;
        }
        
	private:
		WindVector wind_;
		WindVector potential_;
	};
}

#endif /* defined(__Sniffer_Cxx__Wind__) */
