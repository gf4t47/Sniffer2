//
//  DetectionInitializer.h
//  SnifferCxx
//
//  Created by Ke Ding  on 8/11/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__DetectionInitializer__
#define __SnifferCxx__DetectionInitializer__

#include <memory>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "../model/TypeDef.h"

namespace Model {
	struct Candidate;
}

namespace Initializer {
    struct Detection {
        int time_;
        std::vector<Model::Candidate> detected_;
    };
    
    struct AutoMovement {
        int time_;
        double threshold_;
        Model::unit_t distance_;
    };
    
    class DetectionInitializer {
    public:
        DetectionInitializer(std::string cfg_file, bool json_cfg = true);
        bool loadJson(std::string json_file);
        
        std::shared_ptr<std::vector<Detection>> getDetections() const;
        std::shared_ptr<std::vector<Detection>> getCandidates() const;
        std::shared_ptr<AutoMovement> getAutoMovementInfo() const;
        bool beMultiplethread() const;
        
    private:
        std::shared_ptr<std::vector<Detection>> parseJsonNode(const std::string & nodeName, const boost::property_tree::ptree & pt) const;
        
    private:
        std::shared_ptr<std::vector<Detection>> dects_;
        std::shared_ptr<std::vector<Detection>> can_;
        std::shared_ptr<AutoMovement> auto_movement_;
        bool multiplethread_flag_;
    };
}

#endif /* defined(__SnifferCxx__DetectionInitializer__) */
