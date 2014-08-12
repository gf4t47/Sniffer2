//
//  HypothesisInitializer.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/24/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__HypothesisInitializer__
#define __SnifferCxx__HypothesisInitializer__

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../forward/ForwardChecking.h"

namespace Model {
    class Hypothesis;
}

namespace Backward {
    class BackwardChecking;
}

namespace Forward {
    class ForwardChecking;
}

namespace initializer {
    typedef size_t ideal_t;
    
    class HypothesisInitializer {
    public:
        HypothesisInitializer(std::string cfg_file);
        std::shared_ptr<Backward::BackwardChecking> getBackwardAlg();
		std::shared_ptr<Forward::ForwardChecking> getForwardAlg();
        std::shared_ptr<std::vector<Model::Hypothesis>> getHyptheses();
        ideal_t getIdealCells();
        bool load(std::string cfg_file);
        
    public:
        static std::unordered_map<std::string, std::function<std::shared_ptr<Forward::ForwardChecking>(Forward::range_t)>> String2Forward;
        
    private:
        std::shared_ptr<Backward::BackwardChecking> backward_;
		std::shared_ptr<Forward::ForwardChecking> forward_;
        std::shared_ptr<std::vector<Model::Hypothesis>> hyps_;
        ideal_t ideal_cells_;
    };
}

#endif /* defined(__SnifferCxx__HypothesisInitializer__) */
