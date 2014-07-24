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

namespace Model {
	class Cells;
	class Map3D;
	class Hypothesis;
	class Coordinate;
}

namespace Forward {
	class ForwardChecking {
	public:
        ForwardChecking();
		virtual ~ForwardChecking();

		//************************************
		// Method:    Deduce
		// FullName:  Forward::ForwardChecking::Deduce
		// Access:    virtual public 
		// Returns:   std::shared_ptr<Model::Cells> : all the cells has some amount of methane after calculation.
		// Qualifier:
		// Parameter: const Model::Hypothesis & hypothesis
		// Parameter: const Model::Map3D & map
		// Parameter: size_t count : the number of iterations to calculate.
		//************************************
		virtual std::shared_ptr<Model::Cells> Deduce(const Model::Hypothesis & hypothesis, const Model::Map3D & map, size_t count) const = 0;
        
        virtual std::shared_ptr<std::vector<Model::Hypothesis>> UpdateMethane(const std::vector<Model::Hypothesis> & hyps, const Model::Map3D & map, size_t count) const;

		virtual double calcGaussianBlurMean(const Model::Coordinate & location, const Model::Cells & methane_cells, const Model::Map3D & map) const;
	};

}

#endif /* defined(__SnifferCxx__ForwardChecking__) */
