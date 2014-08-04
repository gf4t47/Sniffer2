//
//  Gaussian.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "Gaussian.h"
#include <random>

namespace Math {
    using namespace std;
    using namespace Model;
    
    default_random_engine generator;
    
    //************************************
	// Method:    calcGaussianSamples : Gaussian wind vectors generated by mean and cov(calculated by unit)
	// FullName:  Forward::UpdateByCell::calcGaussianSamples
	// Access:    private
	// Returns:   shared_ptr<vector<WindVector>> : a list of random wind vecotrs
	// Qualifier: const
	// Parameter: const WindVector & mean
	// Parameter: const unit_t unit : cell unit
	// Parameter: const size_t num : the length of return list.
	//************************************
	shared_ptr<vector<WindVector>> Gaussian::RandomWindVectors(const WindVector & mean, const unit_t range, const size_t num) {
//        vector<shared_ptr<default_random_engine>> generators;
//        default_random_engine generator;
		vector<normal_distribution<wv_item_t>> distributions;
        
		for (auto m : mean) {
//            generators.push_back(make_shared<default_random_engine>(default_random_engine()));
			distributions.push_back(normal_distribution<wv_item_t>(m, range));
		}
        
		auto ret = make_shared<vector<WindVector>>();
//        cout << "mean="<<mean << endl;
		for (int i = 0; i < num; i++) {
			WindVector wv;
			for (int j = 0; j < distributions.size(); j++) {
				wv[j] = distributions[j](generator);
			}
//            cout << wv << endl;
			ret->push_back(wv);
		}
        
		return ret;
	}
}