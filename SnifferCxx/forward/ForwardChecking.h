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
//    const int blur_range = 3;
    
	class ForwardChecking {
	public:
        ForwardChecking(int blur_range);
		virtual ~ForwardChecking();

		std::shared_ptr<Model::Cells> Deduce(Model::Hypothesis & hypothesis, const Model::Map3D & map, size_t count) const;
        std::shared_ptr<std::vector<Model::Hypothesis>> UpdateMethane(const std::vector<Model::Hypothesis> & hyps, const Model::Map3D & map, size_t count) const;
		virtual double calcGaussianBlurMean(const Model::Coordinate & location, const Model::Cells & methane_cells, const Model::Map3D & map) const;
        
    protected:
		virtual std::shared_ptr<Model::Cells> calcEnds(const Model::Cells & cells, const Model::Map3D & map) const = 0;
        
    protected:
        int getBlurRange() const;
        
    private:
        int blur_range_;
	};

}

#endif /* defined(__SnifferCxx__ForwardChecking__) */
