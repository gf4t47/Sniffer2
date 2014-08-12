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

namespace initializer {
	using namespace std;
	using namespace Model;
	using namespace Backward;
	using namespace Forward;
    
    const Forward::range_t default_blurRange = 1;
    const Backward::range_t default_kernelRange = 1;
    
    const string strBlurRange = "blurRange";
    const string strKernelRange = "kernelRange";
    const string strForwardChecking = "forwardChecking";
    const string strHypothesis = "hypothesis";
    const string strLocation = "location";
    const string strConcentration = "concentration";
    const string strIdealCells = "outputCells";
    
    unordered_map<string, function<shared_ptr<ForwardChecking>(Forward::range_t)>> HypothesisInitializer::String2Forward =
    {
		{ "byCell", [](Forward::range_t range){return make_shared<UpdateByCell>(range); } },
		{ "byBlur", [](Forward::range_t range){return make_shared<UpdateByConvolution>(range); } },
		{ "byParticle", [](Forward::range_t range){return nullptr; } }
    };
    
    HypothesisInitializer::HypothesisInitializer(string cfg_file)
        :hyps_(make_shared<vector<Hypothesis>>()) {
        load(cfg_file);
    }
    
    shared_ptr<BackwardChecking> HypothesisInitializer::getBackwardAlg() {
        return backward_;
    }

	shared_ptr<ForwardChecking> HypothesisInitializer::getForwardAlg() {
		return forward_;
	}
    
    shared_ptr<vector<Hypothesis>> HypothesisInitializer::getHyptheses() {
        return hyps_;
    }
    
    ideal_t HypothesisInitializer::getIdealCells() {
        return ideal_cells_;
    }
    
    bool HypothesisInitializer::load(string cfg_file) {
        using boost::property_tree::ptree;
        using boost::lexical_cast;
        
        ptree pt;
        read_json(cfg_file, pt);
        
        auto blur_range = default_blurRange;
        auto blurRange_node = pt.get_optional<Backward::range_t>(strBlurRange);
        if (blurRange_node) {
            blur_range = *blurRange_node;
        }
        
        auto kernel_range = default_kernelRange;
        auto kernelRange_node = pt.get_optional<Forward::range_t>(strKernelRange);
        if (kernelRange_node) {
            kernel_range = *kernelRange_node;
        }
        
        auto ideal_cells_node = pt.get_optional<ideal_t>(strIdealCells);
        if (ideal_cells_node) {
            ideal_cells_ = *ideal_cells_node;
        }
        else {
            ideal_cells_ = numeric_limits<ideal_t>::max();
        }
        
        forward_ = make_shared<UpdateByCell>(kernel_range);
        auto forward_node = pt.get_optional<string>(strForwardChecking);
        if (forward_node) {
            auto find_ret = String2Forward.find(*forward_node);
            if (find_ret != String2Forward.end()) {
                forward_ = (find_ret->second)(kernel_range);
            }
        }
        
        backward_ = make_shared<BackwardChecking>(blur_range, kernel_range);
        
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