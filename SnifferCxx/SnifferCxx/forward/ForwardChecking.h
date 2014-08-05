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
    class Cell;
	class Cells;
	class Map3D;
	class Hypothesis;
	class Coordinate;
}

namespace Forward {
    typedef int kernel_range_t;
    
	class ForwardChecking {
	public:
        ForwardChecking(kernel_range_t kernel_range);
		virtual ~ForwardChecking();

		std::shared_ptr<Model::Cells> Deduce(Model::Hypothesis & hypothesis, const Model::Map3D & map, size_t count) const;
        void UpdateMethane(std::shared_ptr<std::vector<Model::Hypothesis>> hyps, const Model::Map3D & map, size_t count) const;

		void operator()(const std::vector<Model::Hypothesis> & hyps, const Model::Map3D & map);
		        
    protected:
		virtual std::shared_ptr<Model::Cells> calcEnds(const Model::Cells & cells, const Model::Map3D & map) const = 0;
        kernel_range_t getKernelRange() const;
        
    private:
        kernel_range_t kernel_range_;
	};

}

#endif /* defined(__SnifferCxx__ForwardChecking__) */
