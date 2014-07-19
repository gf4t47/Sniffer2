//
//  testMap3D.cpp
//  testSnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#define BOOST_TEST_MODULE testMap3D
#include <boost/test/unit_test.hpp>
#include "../../SnifferCxx/model/Map3D.h"
#include "../../SnifferCxx/model/Cell.h"
#include "../../SnifferCxx/model/Coordinate.h"
#include "../../SnifferCxx/model/Wind.h"
#include "../../SnifferCxx/model/Methane.h"

using namespace std;

BOOST_AUTO_TEST_CASE(UpdateCell)
{
	using namespace Model;
    
    Map3D m1(100, 50, 10);
    Cell c1(Coordinate(5, 3, 4), CellTag::Air, Methane(), Wind());
    
    m1.UpdateCell(c1);
    
    auto ret_c = m1.getCell(c1.getCoordinate());
    
}
