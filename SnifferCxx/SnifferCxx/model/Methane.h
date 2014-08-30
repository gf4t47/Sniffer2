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
		Methane(mtn_t c);
		Methane(mtn_t c, const WindVector & wv);

		static double getBackground();
		double getMethane() const;
		mtn_t getConcentration() const;
		const WindVector & getPotential() const;

		//bool operator== (const Methane & oth) const;
		Methane operator+ (const Methane & oth) const;

		friend std::ostream& operator<<(std::ostream& os, const Methane& mtn);
		//friend std::ofstream& operator<<(std::ofstream& fs, const Methane& mtn);
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & concentration_;
			ar & potential_;
        }

	protected:
		bool updateConcentration(mtn_t concentration);

	private:
		mtn_t concentration_;
		WindVector potential_;
	};
}

#endif /* defined(__Sniffer_Cxx__Methane__) */
