//
//  InformationGain.h
//  SnifferCxx
//
//  Created by Ke Ding  on 8/5/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__InformationGain__
#define __SnifferCxx__InformationGain__

#include <vector>
#include <memory>

namespace Support {
	class MyLog;
}

namespace Model {
    class Coordinate;
    class Hypothesis;
	class Hypotheses;
    class Map3D;
}

namespace Forward {
    class ForwardChecking;
}

namespace Backward {
    typedef double entropy_t;
    
    class BackwardChecking;
    
    class InformationGain {
    public:
        InformationGain(const Forward::ForwardChecking & forward, const BackwardChecking & backward, const Model::Map3D & map);
        virtual ~InformationGain();
        
        std::vector<entropy_t> calcInforGains(const std::vector<Model::Coordinate> & candidates, const Model::Hypotheses & hyps, int time_count) const;
        
	protected:
        entropy_t calcInforGain(const Model::Coordinate & candidate, const Model::Hypotheses & hyps, const Model::Hypotheses & future_hyps) const;

	private:
        entropy_t entropy(const Model::Hypotheses & hyps) const;
        
    private:
        const Forward::ForwardChecking & forward_;
        const BackwardChecking & backward_;
        const Model::Map3D & map_;
		static std::unique_ptr<Support::MyLog> lg_;
    };
}

#endif /* defined(__SnifferCxx__InformationGain__) */
