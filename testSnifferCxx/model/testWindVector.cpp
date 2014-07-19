//
//  testWindVector.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#define BOOST_TEST_MODULE testWindVector
#include <boost/test/unit_test.hpp>
#include "../../SnifferCxx/model/WindVector.h"

using namespace std;

BOOST_AUTO_TEST_CASE(testOperatorPlus)
{
	using namespace Model;

	WindVector w1{ 1, 2, 3 };
	WindVector w2{ 2, 3, 4 };

	WindVector w3{ 3, 5, 7 };

	auto ret = w1 + w2;
	BOOST_CHECK_EQUAL(ret, w2);
}
