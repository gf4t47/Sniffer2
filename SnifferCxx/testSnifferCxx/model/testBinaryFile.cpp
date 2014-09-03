//
//  testWindVector.cpp
//  Sniffer_Cxx
//
//  Created by Ke Ding  on 7/17/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "../../SnifferCxx/model/Candidate.h"
#include <fstream>

using namespace std;
using namespace Model;

BOOST_AUTO_TEST_CASE(testCoordinateBinary)
{
	Coordinate c1(1, 2, 3);
	ofstream out("test.bin", ios::out | ios::trunc | ios::binary);
	out << c1;
}
