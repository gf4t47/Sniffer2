//
//  MapBuilder.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/24/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__MapBuilder__
#define __SnifferCxx__MapBuilder__

#include <string>
#include <vector>
#include <boost/optional.hpp>
#include "../model/Coordinate.h"
#include "../model/WindVector.h"

namespace Model {
    class Map3D;
}

namespace initializer {
    struct stBuilding {
        Model::Coordinate location_;
        Model::Coordinate boundary_;
    };
    
    class MapBuilder
    {
    public:
        MapBuilder(Model::coord_item_t length, Model::coord_item_t width, Model::coord_item_t height, Model::unit_t unit);
        MapBuilder(const Model::Coordinate & boundary, Model::unit_t unit);
        MapBuilder(const std::string & cfg_file);
        
        MapBuilder * setStartIndex(const Model::Coordinate & startIndex);
        MapBuilder * setWind(const Model::WindVector & wind);
        MapBuilder * setBuildings(const std::vector<stBuilding> & buildings);
        MapBuilder * setLocalPotential(Model::coord_item_t step);
        
        std::shared_ptr<Model::Map3D> build();
        
    private:
        bool load(const std::string & filename);
        void save(const std::string & filename);
        
    private:
        Model::unit_t unit_;
        Model::Coordinate boundary_;
        Model::coord_item_t potentialStep_;
        boost::optional<Model::Coordinate> startIndex_;
        boost::optional<Model::WindVector> wind_;
        std::vector<stBuilding> buildings_;
    };
}


#endif /* defined(__SnifferCxx__MapBuilder__) */
