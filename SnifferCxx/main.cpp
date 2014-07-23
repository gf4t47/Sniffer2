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
#include <boost/lexical_cast.hpp>
#include "model/Map3D.h"

using namespace std;
using namespace Model;

struct map_setting {
private:  
    const string strLocation = "location";
    const string strBoundary = "boundary";
    const string strWind = "wind";
    const string strBuilding = "building";
    const string strUnit = "unit";
    const string strPotential = "potential";
    
public:
    unit_t unit_;
    Coordinate boundary_;
    WindVector wind_;
    boost::optional<coord_item_t> potential_;
    boost::optional<Coordinate> location_;
    vector<stBuilding> buildings_;
    
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
    
    potential_ = pt.get_optional<coord_item_t>(strPotential);
    
    auto node_boundary = pt.get_child(strBoundary);
	transform(node_boundary.begin(), node_boundary.end(), boundary_.begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data()); });
    
    auto node_location = pt.get_child_optional(strLocation);
    if (node_location) {
		Coordinate temp(0,0,0);
		location_ = temp;
        transform(node_location->begin(), node_location->end(), (*location_).begin(), [](ptree::value_type & v){return lexical_cast<coord_item_t>(v.second.data());});
    }
    
    auto node_wind = pt.get_child(strWind);
    transform(node_wind.begin(), node_wind.end(), wind_.begin(), [](ptree::value_type & v){return lexical_cast<wv_item_t>(v.second.data());});
    
    auto node_buildings = pt.get_child_optional(strBuilding);
    if (node_buildings) {
        for (auto node_building : *node_buildings) {
            auto node_bld_tree = node_building.second;

            stBuilding building;
            
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
    map_setting ms;
    ms.load(argv[1]);

	auto builder = make_shared<MapBuilder>(ms.boundary_, ms.unit_);
	if (ms.location_)
	{
		builder->setStartIndex(*ms.location_);
	}
    
    if (ms.potential_) {
        builder->setLocalPotential(*ms.potential_);
    }
	
	auto map = builder->setWind(ms.wind_)->setBuildings(ms.buildings_)->build();

    
    return 0;
}

