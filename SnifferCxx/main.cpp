//
//  main.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <iostream>
#include "model/Map3D.h"
#include "model/Cell.h"
#include "model/Coordinate.h"
#include "model/Wind.h"
#include "model/Methane.h"

using namespace std;

int main(int argc, const char * argv[])
{
	using namespace Model;
    
    Map3D m1(100, 50, 10, 1);
    
    Coordinate coord1(3,4,5);
    Coordinate coord2(1,2,3);
    Methane mtn1(25.0f);
    Wind w1;
    
    Cell c1(coord1, CellTag::Air, mtn1, w1);
    
    m1.updateCell(c1);
    
    auto ret_val = m1.getCell(coord1);
    auto coord3 = ret_val.getCoordinate();
    coord3 = coord2;
    cout<<"ret = "<< ret_val;
    cout<<"map = "<< m1.getCell(coord1);
}

