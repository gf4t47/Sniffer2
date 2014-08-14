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

namespace Initializer {
    struct Detection {
        int time_;
        std::vector<Model::Leak> detected_;
    };
    
    class DetectionInitializer {
    public:
        static std::tuple<std::shared_ptr<std::vector<Detection>>, std::shared_ptr<std::vector<Detection>>, bool> load(std::string filename);
    };
}

#endif /* defined(__SnifferCxx__DetectionInitializer__) */
