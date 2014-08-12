//
//  DetectionInitializer.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 8/11/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "DetectionInitializer.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>

namespace initializer {
    using namespace std;
    using namespace Model;
    
    const string strDetection = "detection";
    const string strTime = "time";
    const string strLeak = "leak";
    const string strLocation = "location";
    const string strConcentration = "concentration";
    const string strRepeat = "repeat";
    const string strMultithread = "multithread";
    
    tuple<shared_ptr<vector<detection>>, bool> DetectionInitializer::load(string filename) {
        using boost::property_tree::ptree;
        using boost::lexical_cast;
        
        ptree pt;
        read_json(filename, pt);
        
        auto dect_vec = make_shared<vector<detection>>();
        
        auto multithread = pt.get<bool>(strMultithread);
        
        for (auto dect_node : pt.get_child(strDetection)) {
            auto dect = dect_node.second;
            
            detection detection;
            
            detection.time_ = dect.get<int>(strTime);
            for (auto leak_node : dect.get_child(strLeak)) {
                auto leak = leak_node.second;
                
                Leak detected;
                auto location = leak.get_child(strLocation);
                transform(location.begin(), location.end(), detected.location_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
                detected.concentration_ = leak.get<mtn_t>(strConcentration);
                
                detection.detected_.push_back(detected);
            }
            
            auto repeat = dect.get<size_t>(strRepeat);
            for (auto i = 0; i < repeat; i++) {
                dect_vec->push_back(detection);
            }
        }
        
        return make_tuple(dect_vec, multithread);
    }

}