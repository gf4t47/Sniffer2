//
//  ForwardChecking.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__ForwardChecking__
#define __SnifferCxx__ForwardChecking__

#include <memory>
#include <vector>
#include <boost/logic/tribool.hpp>
#include "../model/TypeDef.h"

namespace Model {
    class Cell;
	class Cells;
	class Map3D;
	class Hypothesis;
	class Hypotheses;
	class Coordinate;
}

namespace Forward {   
	using Model::range_t;

	class ForwardChecking {

	public:
        ForwardChecking(range_t kernel_range);
		virtual ~ForwardChecking();

		std::shared_ptr<Model::Cells> Deduce(Model::Hypothesis & hypothesis, const Model::Map3D & map, size_t count) const;
        std::shared_ptr<Model::Hypotheses> UpdateMethane(Model::Hypotheses & hyps, const Model::Map3D & map, size_t count) const;

		void update_once(Model::Hypotheses & hyps, const Model::Map3D & map) const;
				        
    protected:
		virtual std::shared_ptr<Model::Cells> calcEnds(const Model::Cells & cells, const Model::Map3D & map) const = 0;
        range_t getKernelRange() const;
        
    private:
        range_t kernel_range_;
	};

}

#endif /* defined(__SnifferCxx__ForwardChecking__) */
