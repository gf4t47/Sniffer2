//
//  Methane.h
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __Sniffer_Cxx__Methane__
#define __Sniffer_Cxx__Methane__

#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "WindVector.h"

namespace Model {
	typedef double mtn_t;

	class Methane {
	public:
		Methane();
		Methane(mtn_t c, const WindVector & wv);

		static double getBackground();
		double getMethane() const;
		mtn_t getParticleNum() const;

		bool updateMethane(mtn_t concentration);

		bool operator== (const Methane & oth) const;

		friend std::ostream& operator<<(std::ostream& os, const Methane& mtn);
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & concentration_;
        }

	private:
		mtn_t concentration_;
		WindVector potential_;
	};
}

#endif /* defined(__Sniffer_Cxx__Methane__) */
