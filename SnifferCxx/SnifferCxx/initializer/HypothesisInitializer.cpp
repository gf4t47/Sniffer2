//
//  HypothesisInitializer.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/24/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "HypothesisInitializer.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include "../backwrad/BackwardChecking.h"
#include "../forward/UpdateByCell.h"
#include "../forward/UpdateByConvolution.h"
#include "../model/Coordinate.h"

using namespace std;
using namespace Model;
using namespace Backward;
using namespace Forward;

namespace initializer {
    using namespace std;
    
    const int default_blurRange = 2;
    
    const string strBlurRange = "blurRange";
    const string strForwardChecking = "forwardChecking";
    const string strHypothesis = "hypothesis";
    const string strLocation = "location";
    const string strConcentration = "concentration";
    
    unordered_map<string, function<shared_ptr<ForwardChecking>(int)>> HypothesisInitializer::String2Forward =
    {
        {"byCell", [](int blur_range){return make_shared<UpdateByCell>(blur_range);}},
        {"byBlur", [](int blur_range){return make_shared<UpdateByConvolution>(blur_range);}},
        {"byParticle", [](int blur_range){return nullptr;}}
    };
    
    HypothesisInitializer::HypothesisInitializer(string cfg_file)
        :hyps_(make_shared<vector<Hypothesis>>()) {
        load(cfg_file);
    }
    
    shared_ptr<BackwardChecking> HypothesisInitializer::getCheckingAlg() {
        return alg_;
    }
    
    shared_ptr<vector<Hypothesis>> HypothesisInitializer::getHyptheses() {
        return hyps_;
    }
    
    bool HypothesisInitializer::load(string cfg_file) {
        using boost::property_tree::ptree;
        using boost::lexical_cast;
        
        ptree pt;
        read_json(cfg_file, pt);
        
        auto blur_range = default_blurRange;
        auto blurRange_node = pt.get_optional<int>(strBlurRange);
        if (blurRange_node) {
            blur_range = *blurRange_node;
        }
        
        shared_ptr<ForwardChecking> forward_ptr = make_shared<UpdateByConvolution>(blur_range);
        auto forward_node = pt.get_optional<string>(strForwardChecking);
        if (forward_node) {
            auto find_ret = String2Forward.find(*forward_node);
            if (find_ret != String2Forward.end()) {
                forward_ptr = (find_ret->second)(blur_range);
            }
        }
        
        alg_ = make_shared<BackwardChecking>(forward_ptr);
        
        auto hyp_node = pt.get_child_optional(strHypothesis);
        if (hyp_node) {
            vector<vector<Leak>> all_hypothesis_leaks;
            for (auto hyp : *hyp_node) {
                auto hyp_tree = hyp.second;
                
                Leak leak;
                auto node_location = hyp_tree.get_child(strLocation);
                transform(node_location.begin(), node_location.end(), leak.location_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
                
                leak.concentration_ = hyp_tree.get<mtn_t>(strConcentration);
                
                vector<Leak> leak_vec;
                leak_vec.push_back(leak);
                
                all_hypothesis_leaks.push_back(leak_vec);
            }
            
            for (auto leak_vec : all_hypothesis_leaks) {
                Hypothesis hyp(leak_vec, 1.0 / (double)all_hypothesis_leaks.size());
                hyps_->push_back(hyp);
            }
        }
        
        return false;
    }
}