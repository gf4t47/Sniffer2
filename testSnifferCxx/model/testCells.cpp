//
//  testMap3D.cpp
//  testSnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <boost/test/unit_test.hpp>
#include "../../SnifferCxx/model/Cells.h"

using namespace std;
using namespace Model;

BOOST_AUTO_TEST_CASE(testMergeCells)
{
	Coordinate c1(0, 0, 1);
	Coordinate c2(0, 0, 2);
	Coordinate c3(0, 0, 3);

	WindVector wv1(1.0, 1.0, 1.0);
	Methane mtn1(100);
	Wind w1(wv1);

	Cell a1(c1, CellTag::Air, mtn1, w1);
	Cell a2(c2, CellTag::Air, mtn1, w1);
	Cell a3(c3, CellTag::Air, mtn1, w1);

	Cell b1(c1, CellTag::Building, mtn1, w1);
	Cell b2(c2, CellTag::Building, mtn1, w1);
	Cell b3(c3, CellTag::Building, mtn1, w1);

	Cell g1(c1, CellTag::Ground, mtn1, w1);
	Cell g2(c2, CellTag::Ground, mtn1, w1);
	Cell g3(c3, CellTag::Ground, mtn1, w1);

	Cells cells1;
	cells1.updateCell(a1);
	cells1.updateCell(a2);
	cells1.updateCell(a3);

	Cells cells2;
	cells2.updateCell(b1);

	Cells cells3;
	cells3.updateCell(g3);

	cells1.mergeCellsByAddMethane(cells2);
	cout << *cells1.getCell(c1);

	cells1.mergeCellsByAddMethane(cells3);
	cout << *cells1.getCell(c3);



}