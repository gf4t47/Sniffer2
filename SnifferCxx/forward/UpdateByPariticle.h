//
//  UpdateByPariticle.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__UpdateByPariticle__
#define __SnifferCxx__UpdateByPariticle__

#include "ForwardChecking.h"

namespace Forward {
    class UpdateByParticle : public ForwardChecking {
    public:
        ~UpdateByParticle();
        virtual std::shared_ptr<Model::Cells> Deduce(const Model::Hypothesis & hypothesis, const Model::Map3D & map, size_t count) = 0;
    };
}

#endif /* defined(__SnifferCxx__UpdateByPariticle__) */
