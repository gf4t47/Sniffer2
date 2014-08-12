//
//  DetectionInitializer.h
//  SnifferCxx
//
//  Created by Ke Ding  on 8/11/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__DetectionInitializer__
#define __SnifferCxx__DetectionInitializer__

#include "../model/Hypothesis.h"
#include <memory>

namespace initializer {
    struct detection {
        int time_;
        std::vector<Model::Leak> detected_;
    };
    
    class DetectionInitializer {
    public:
        static std::tuple<std::shared_ptr<std::vector<detection>>, bool> load(std::string filename);
        
    };
}

#endif /* defined(__SnifferCxx__DetectionInitializer__) */
