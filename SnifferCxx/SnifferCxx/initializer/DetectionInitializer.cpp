//
//  DetectionInitializer.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 8/11/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "DetectionInitializer.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>

namespace Initializer {
    using namespace std;
    using namespace Model;
    
    using boost::property_tree::ptree;
    
    DetectionInitializer::DetectionInitializer(string cfg_file) {
        load(cfg_file);
    }
    
    shared_ptr<vector<Detection>> DetectionInitializer::parseJsonNode(const string & nodeName, const boost::property_tree::ptree & pt) {
        const string strTime = "time";
        const string strDect = "dect";
        const string strLocation = "location";
        const string strConcentration = "concentration";
        const string strRepeat = "repeat";
        
        using boost::lexical_cast;
        
        auto ret_vec = make_shared<vector<Detection>>();
        
        for (auto dect_node : pt.get_child(nodeName)) {
            auto dect = dect_node.second;
            
            Detection detection;
            
            detection.time_ = dect.get<int>(strTime);
            for (auto leak_node : dect.get_child(strDect)) {
                auto leak = leak_node.second;
                
                Leak detected;
                auto location = leak.get_child(strLocation);
                transform(location.begin(), location.end(), detected.location_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
                auto concentration_node = leak.get_optional<mtn_t>(strConcentration);
                if (concentration_node) {
                    detected.concentration_ = *concentration_node;
                }
                
                detection.detected_.push_back(detected);
            }
            
            auto repeat = dect.get_optional<size_t>(strRepeat);
            if (repeat) {
                for (auto i = 0; i < *repeat; i++) {
                    ret_vec->push_back(detection);
                }
            }
        }
        
        return ret_vec;
    }
    
    bool DetectionInitializer::load(string filename) {
        const string strDetection = "detection";
        const string strCandidate = "candidate";
        const string strMultithread = "multithread";
        
        ptree pt;
        read_json(filename, pt);
        
        multiplethread_flag_ = pt.get<bool>(strMultithread);
        
        dects_ = parseJsonNode(strDetection, pt);

        can_ = parseJsonNode(strCandidate, pt);
        
        return true;
    }
    
    shared_ptr<vector<Detection>> DetectionInitializer::getDetections() {
        return dects_;
    }
    
    shared_ptr<vector<Detection>> DetectionInitializer::getCandidates() {
        return can_;
    }
    
    bool DetectionInitializer::beMultiplethread() {
        return multiplethread_flag_;
    }

}