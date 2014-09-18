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
#include "../backward/BackwardChecking.h"
#include "../forward/UpdateByCell.h"
#include "../forward/UpdateByConvolution.h"
#include "../model/Coordinate.h"
#include "../model/Candidate.h"
#include "../model/Hypotheses.h"
#include "../model/Methane.h"


namespace Initializer {
	using namespace std;
	using namespace Model;
	using namespace Backward;
	using namespace Forward;
    
    unordered_map<string, function<shared_ptr<ForwardChecking>(range_t, int it_per_sec)>> HypothesisInitializer::String2Forward =
    {
		{ "byCell", [](range_t range, int iteration_per_sec){return make_shared<UpdateByCell>(range, iteration_per_sec); } },
		{ "byBlur", [](range_t range, int iteration_per_sec){return make_shared<UpdateByConvolution>(range, iteration_per_sec); } },
		{ "byParticle", [](range_t range, int iteration_per_sec){return nullptr; } }
    };
    
    HypothesisInitializer::HypothesisInitializer(string cfg_file)
        :hyps_(make_shared<Hypotheses>()) {
        load(cfg_file);
    }
    
    shared_ptr<BackwardChecking> HypothesisInitializer::getBackwardAlg() const {
        return backward_;
    }

	shared_ptr<ForwardChecking> HypothesisInitializer::getForwardAlg() const {
		return forward_;
	}
    
    shared_ptr<Hypotheses> HypothesisInitializer::getHyptheses() const {
        return hyps_;
    }
    
    ideal_t HypothesisInitializer::getIdealCells() const {
        return ideal_cells_;
    }

	bool HypothesisInitializer::getDetectionOnly() const {
		return output_detection_only_;
	}
    
    bool HypothesisInitializer::load(string cfg_file) {
        const range_t default_blurRange = 1;
        const range_t default_kernelRange = 1;
		const range_t default_variance = 128;
        
        const string strBlurRange = "GaussianblurRange";
        const string strKernelRange = "GaussiankernelRange";
		const string strGammaVariance = "GammaVariance";
        const string strForwardChecking = "forwardChecking";
		const string strIterations = "iterations_per_second";
        const string strHypothesis = "hypothesis";
        const string strLocation = "location";
        const string strConcentration = "concentration";
        const string strIdealCells = "outputCells";
		const string strDetectionOnly = "output_detection_only";
		const string strBackground = "concentration_background";
		const string strConcPerParticle = "concentration_per_particle";
        
        using boost::property_tree::ptree;
        using boost::lexical_cast;
        
        ptree pt;
        read_json(cfg_file, pt);
        
        auto blur_range = default_blurRange;
        auto blurRange_node = pt.get_optional<range_t>(strBlurRange);
        if (blurRange_node) {
            blur_range = *blurRange_node;
        }
        
        auto kernel_range = default_kernelRange;
        auto kernelRange_node = pt.get_optional<range_t>(strKernelRange);
        if (kernelRange_node) {
            kernel_range = *kernelRange_node;
        }

		auto variance = default_variance;
		auto variance_node = pt.get_optional<range_t>(strGammaVariance);
		if (variance_node) {
			variance = *variance_node;
		}
        
        auto ideal_cells_node = pt.get_optional<ideal_t>(strIdealCells);
        if (ideal_cells_node) {
            ideal_cells_ = *ideal_cells_node;
        }
        else {
			ideal_cells_ = numeric_limits<ideal_t>::max();
        }

		auto detection_only_node = pt.get_optional<bool>(strDetectionOnly);
		if (detection_only_node) {
			output_detection_only_ = *detection_only_node;
		}
		else {
			output_detection_only_ = false;
		}

		auto iterations_per_second = 5;
		auto iiterations_node = pt.get_optional<int>(strIterations);
		if (iiterations_node) {
			iterations_per_second = *iiterations_node;
		}
        
        forward_ = make_shared<UpdateByCell>(kernel_range, iterations_per_second);
        auto forward_node = pt.get_optional<string>(strForwardChecking);
        if (forward_node) {
            auto find_ret = String2Forward.find(*forward_node);
            if (find_ret != String2Forward.end()) {
                forward_ = (find_ret->second)(kernel_range, iterations_per_second);
            }
        }
        
        backward_ = make_shared<BackwardChecking>(blur_range, kernel_range, variance);

		auto background = pt.get<double>(strBackground);
		Methane::setBackgournd(background);

		auto pperp = pt.get<double>(strConcPerParticle);
		Methane::setConcPerParticle(pperp);
        
        auto hyp_node = pt.get_child_optional(strHypothesis);
        if (hyp_node) {
            vector<vector<Candidate>> all_hypothesis_leaks;
            for (auto hyp : *hyp_node) {
                auto hyp_val = hyp.second;

				vector<Candidate> leak_vec;
				for (auto leak_node : hyp.second) {
					Candidate leak;
					leak.concentration_ = leak_node.second.get<mtn_t>(strConcentration);

					auto node_location = leak_node.second.get_child(strLocation);
					transform(node_location.begin(), node_location.end(), leak.location_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data()); });

					leak_vec.push_back(leak);
				}                
                all_hypothesis_leaks.push_back(leak_vec);
            }
            
            for (auto leak_vec : all_hypothesis_leaks) {
                Hypothesis hyp(leak_vec, 1.0 / static_cast<double>(all_hypothesis_leaks.size()));
                hyps_->push_back(hyp);
            }

			return true;
        }
        
        return false;
    }
}