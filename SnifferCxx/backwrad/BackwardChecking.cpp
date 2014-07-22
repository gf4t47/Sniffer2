//
//  BackwardChecking.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "BackwardChecking.h"
#include "../forward/UpdateByCell.h"
#include "../model/Map3D.h"
#include "../stactistic/Gamma.h"

namespace Backward {
    const double gamma_scale = 1.0;
    
    using namespace std;
    using namespace Model;
    using namespace Forward;
    
    BackwardChecking::BackwardChecking()
        :forward_(new UpdateByCell()) {
        
    }
    
    BackwardChecking::~BackwardChecking() {
        
    }
    
    double BackwardChecking::calcGaussianBlurMean(const Coordinate & location, const Cells & methane_cells) const {
        return 0.0f;
    }
    
    double BackwardChecking::calcLikehood(const Hypothesis & hyp, const Coordinate & detected_location, double detected_concentration) const {
        auto mean = calcGaussianBlurMean(detected_location, *hyp.getMethaneCells());
        return Stactistic::Gamma::calcGammaPdf(mean, gamma_scale, detected_concentration);
    }
    
    void BackwardChecking::normalize(vector<Hypothesis> &hyps) const{
        auto sum = accumulate(hyps.begin(), hyps.end(), 0.0f, [](double sum, const Hypothesis & hyp){ return sum += hyp.getProbability();});
        for_each(hyps.begin(), hyps.end(), [sum](Hypothesis & hyp){hyp.setProbability(hyp.getProbability() / sum);});
    }
    
    shared_ptr<vector<Hypothesis>> BackwardChecking::updateHypothesises(const vector<Hypothesis> & hyps, const Map3D & map, size_t time_count, const vector<Leak> & detections) const {
        auto new_hyps = forward_->UpdateMethane(hyps, map, time_count);
        
        for (auto hyp : *new_hyps) {
            auto likeHood = 1.0f;
            for (auto detection : detections) {
                likeHood *= calcLikehood(hyp, detection.location_, detection.concentration_);
            }
            hyp.setProbability(hyp.getProbability() * likeHood);
        }
        
        normalize(*new_hyps);
        
        return new_hyps;
    }
    
    
}