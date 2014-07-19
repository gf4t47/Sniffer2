//
//  ForwardChecking.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__ForwardChecking__
#define __SnifferCxx__ForwardChecking__

#include <iostream>
#include <memory>
#include "../model/Cells.h"
#include "../model/Map3D.h"

namespace Forward {
    class ForwardChecking {
    public:
        virtual ~ ForwardChecking();
        
        virtual std::shared_ptr<Model::Cells> Deduce(std::shared_ptr<Model::Cells> cells, Model::Map3D & map, size_t count) = 0;
    };
    
}

#endif /* defined(__SnifferCxx__ForwardChecking__) */
