//
//  ForwardChecking.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "ForwardChecking.h"
#include "../model/Hypothesis.h"

namespace Forward {
    using namespace std;
    using namespace Model;
    
    ForwardChecking::ForwardChecking() {
        
    }
    
	ForwardChecking::~ForwardChecking() {

	}
    
    shared_ptr<vector<Hypothesis>> ForwardChecking::UpdateMethane(const vector<Hypothesis> & hyps, const Map3D & map, size_t count) const {
        auto ret_hyps = make_shared<vector<Hypothesis>>();
        
        for (auto hyp : hyps) {
            auto newCells = Deduce(hyp, map, count);
            Hypothesis newHyp(hyp.getLeaks(), hyp.getProbability(), newCells);
            ret_hyps->push_back(newHyp);
        }
        
        return ret_hyps;
    }
}