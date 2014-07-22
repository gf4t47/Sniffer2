//
//  UpdateByPariticle.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "UpdateByPariticle.h"
#include "../model/Cells.h"
#include "../model/Map3D.h"
#include "../model/Hypothesis.h"

namespace Forward {
    using namespace std;
    using namespace Model;
    
    shared_ptr<Model::Cells> UpdateByParticle::Deduce(const Hypothesis & hypothesis, const Map3D & map, size_t count) {
        return nullptr;
    }
}
