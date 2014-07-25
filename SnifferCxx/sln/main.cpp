//
//  main.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "../sln/MapBuilder.h"

int main(int argc, const char * argv[])
{
    sln::MapBuilder mb(argv[1]);
    auto map = mb.build();
    
    
    
    return 0;
}

