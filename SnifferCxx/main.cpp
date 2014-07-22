//
//  main.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/18/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include "model/Map3D.h"

using namespace std;
using namespace Model;

struct map_setting {
private:
    struct building {
        Coordinate location_;
        Coordinate boundary_;
    };
    
    const string strLocation = "location";
    const string strBoundary = "boundary";
    const string strWind = "wind";
    const string strBuilding = "building";
    const string strUnit = "unit";
    
public:
    boost::optional<Coordinate> location_;
    Coordinate boundary_;
    WindVector wind_;
    vector<building> buildings_;
    unit_t unit_;
    
    bool load(const string & filename);
    void save(const string & filename);
};

void map_setting::save(const string &filename) {
    return;
}

bool map_setting::load(const string & filename) {
    using boost::property_tree::ptree;
    using boost::lexical_cast;
    
    ptree pt;
    read_json(filename, pt);
    
    unit_ = pt.get<unit_t>(strUnit);
    
    auto node_boundary = pt.get_child(strBoundary);
    transform(node_boundary.begin(), node_boundary.end(), boundary_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
    
    auto node_location = pt.get_child_optional(strLocation);
    if (node_location) {
        location_ = {{0,0,0}};
        transform(node_location->begin(), node_location->end(), (*location_).begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
    }
    
    auto node_wind = pt.get_child(strWind);
    transform(node_wind.begin(), node_wind.end(), wind_.begin(), [](ptree::value_type & v){return lexical_cast<wv_item_t>(v.second.data());});
    
    auto node_buildings = pt.get_child_optional(strBuilding);
    if (node_buildings) {
        for (auto node_building : *node_buildings) {
            auto node_bld_tree = node_building.second;

            building building;
            
            auto node_location = node_bld_tree.get_child(strLocation);
            transform(node_location.begin(), node_location.end(), building.location_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
            
            auto node_boudnary = node_bld_tree.get_child(strBoundary);
            transform(node_boudnary.begin(), node_boudnary.end(), building.boundary_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
            
            buildings_.push_back(building);
        }
    }

    
    return true;
}

int main(int argc, const char * argv[])
{
    auto cfgfile = argv[1];
    
    map_setting ms;
    ms.load(cfgfile);
    
    unique_ptr<Map3D> map;
    if(ms.location_) {
        map.reset(new Map3D(*ms.location_, ms.boundary_, ms.unit_));
    }
    else {
        map.reset(new Map3D(ms.boundary_[0], ms.boundary_[1], ms.boundary_[2], ms.unit_));
    }
    
    return 0;
}

