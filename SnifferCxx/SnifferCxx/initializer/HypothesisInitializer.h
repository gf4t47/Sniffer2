//
//  HypothesisInitializer.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/24/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__HypothesisInitializer__
#define __SnifferCxx__HypothesisInitializer__

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../model/TypeDef.h"

namespace Model
{
	class Hypothesis;
	class Hypotheses;
}

namespace Backward
{
	class BackwardChecking;
}

namespace Forward
{
	class ForwardChecking;
}

namespace Initializer
{
	typedef size_t ideal_t;

	class HypothesisInitializer
	{
	public:
		HypothesisInitializer(std::string cfg_file);
		std::shared_ptr<Backward::BackwardChecking> getBackwardAlg() const;
		std::shared_ptr<Forward::ForwardChecking> getForwardAlg() const;
		std::shared_ptr<Model::Hypotheses> getHyptheses() const;
		ideal_t getIdealCells() const;
		bool getDetectionOnly() const;
		bool load(std::string cfg_file);

	public:
		static std::unordered_map<std::string, std::function<std::shared_ptr<Forward::ForwardChecking>(Model::range_t, int it_per_sec)>> String2Forward;

	private:
		std::shared_ptr<Backward::BackwardChecking> backward_;
		std::shared_ptr<Forward::ForwardChecking> forward_;
		std::shared_ptr<Model::Hypotheses> hyps_;
		ideal_t ideal_cells_;
		bool output_detection_only_;
	};
}

#endif /* defined(__SnifferCxx__HypothesisInitializer__) */