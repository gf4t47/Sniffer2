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
#include "TypeDef.h"

namespace Model {
	class Methane {
	public:
		Methane();
		Methane(mtn_t p);
		Methane(mtn_t p, const WindVector & wv);

		static double getBackground();
		static double getConcPerParticle();
		static void setBackgournd(double val);
		static void setConcPerParticle(double val);

		mtn_t getMethaneConc() const;
		mtn_t getParitcles() const;
		const WindVector & getPotential() const;

		Methane operator+ (const Methane & oth) const;

		friend std::ostream& operator<<(std::ostream& os, const Methane& mtn);
		std::ofstream& toBinary(std::ofstream& fs) const;
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & concentration_;
			ar & potential_;
        }

	private:
		static mtn_t background_;
		static mtn_t concentration_per_particle_;

		mtn_t particles_;
		WindVector potential_;
	};
}

#endif /* defined(__Sniffer_Cxx__Methane__) */
