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
    class HypothesisInitializer {
    public:
        HypothesisInitializer(std::string cfg_file);
        std::shared_ptr<Backward::BackwardChecking> getCheckingAlg();
        std::shared_ptr<std::vector<Model::Hypothesis>> getHyptheses();
        bool load(std::string cfg_file);
        
    public:
        static std::unordered_map<std::string, std::function<std::shared_ptr<Forward::ForwardChecking>(int)>> String2Forward;
        
    private:
        std::shared_ptr<Backward::BackwardChecking> alg_;
        std::shared_ptr<std::vector<Model::Hypothesis>> hyps_;
    };
}

#endif /* defined(__SnifferCxx__HypothesisInitializer__) */
