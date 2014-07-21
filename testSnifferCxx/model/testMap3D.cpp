//
//  testMap3D.cpp
//  testSnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <boost/test/unit_test.hpp>
#include "../../SnifferCxx/model/Map3D.h"

using namespace std;
using namespace Model;

BOOST_AUTO_TEST_CASE(UpdateCell)
{
	WindVector wv1(1.5, 2.5, 3.5);
	Coordinate coord1(1, 2, 3);
	Methane mtn1(100);
	Wind w1(wv1);
	Cell c1(coord1, CellTag::Air, mtn1, w1);

	Map3D m1(100, 50, 10, 1);
	m1.updateCell(c1);

	auto c2 = m1.getCell(coord1);

	BOOST_CHECK_EQUAL(c1, c2);
}

BOOST_AUTO_TEST_CASE(InsideMapZeroBase)
{
	Map3D m1(100, 50, 10, 1);
	Coordinate x1(0, 0, 0);
	Coordinate x2(105, 0, 0);
	Coordinate x3(99, 0, 9);

	Coordinate y1(-1, 0, 0);
	Coordinate y2(12, 50, 4);
	Coordinate y3(99, 49, 9);

	Coordinate z1(15, 22, -1);

	BOOST_CHECK(m1.insideMap(x1));
	BOOST_CHECK(!m1.insideMap(x2));
	BOOST_CHECK(m1.insideMap(x3));

	BOOST_CHECK(!m1.insideMap(y1));
	BOOST_CHECK(!m1.insideMap(y2));
	BOOST_CHECK(m1.insideMap(y3));

	BOOST_CHECK(indeterminate(m1.insideMap(z1)));
}


BOOST_AUTO_TEST_CASE(InsideMapNegativeBase)
{
	Coordinate base(0, 22, -7);
	Coordinate boundary(100, 50, 10);
	Map3D m1(base, boundary, 1);

	//auto startIndex = m1.getStartIndex();
	//auto mapBoundary = m1.getBoundary();
	//cout << startIndex[0] <<" "<< startIndex[1] <<" " << startIndex[2]<<endl;
	//cout << mapBoundary[0] <<" "<< mapBoundary[1] <<" "<< mapBoundary[2] << endl;

	Coordinate s1(0, 22, -1); //inside
	Coordinate e1(99, 71, 2); //inside
	Coordinate e2(100, 71, 2); //outside 
	Coordinate e3(99, 72, 2); //outside
	Coordinate e4(99, 71, 3); //outside
	BOOST_CHECK(m1.insideMap(s1));
	BOOST_CHECK(m1.insideMap(e1));
	BOOST_CHECK(!m1.insideMap(e2));
	BOOST_CHECK(!m1.insideMap(e3));
	BOOST_CHECK(!m1.insideMap(e4));

	Coordinate x1(0, 0, 0); //outside
	Coordinate x2(105, 0, 0); //outside
	BOOST_CHECK(!m1.insideMap(x1));
	BOOST_CHECK(!m1.insideMap(x2));

	Coordinate y1(-1, 0, 0); //outside
	Coordinate y2(12, 50, 4); //outside
	Coordinate y3(99, 49, 9); //outside
	BOOST_CHECK(!m1.insideMap(y1));
	BOOST_CHECK(!m1.insideMap(y2));
	BOOST_CHECK(!m1.insideMap(y3));

	Coordinate z1(15, 22, -1); //indsie
	BOOST_CHECK(m1.insideMap(z1));
}