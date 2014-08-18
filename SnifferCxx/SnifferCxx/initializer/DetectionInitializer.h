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
#include <boost/property_tree/ptree.hpp>

namespace Initializer {
    struct Detection {
        int time_;
        std::vector<Model::Leak> detected_;
    };
    
    class DetectionInitializer {
    public:
        DetectionInitializer(std::string cfg_file);
        bool load(std::string filename);
        
        std::shared_ptr<std::vector<Detection>> getDetections();
        std::shared_ptr<std::vector<Detection>> getCandidates();
        bool beMultiplethread();
        
    private:
        std::shared_ptr<std::vector<Detection>> parseJsonNode(const std::string & nodeName, const boost::property_tree::ptree & pt);
        
    private:
        std::shared_ptr<std::vector<Detection>> dects_;
        std::shared_ptr<std::vector<Detection>> can_;
        bool multiplethread_flag_;
    };
}

#endif /* defined(__SnifferCxx__DetectionInitializer__) */
