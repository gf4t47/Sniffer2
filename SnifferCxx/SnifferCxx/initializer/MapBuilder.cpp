//
//  MapBuilder.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/24/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "MapBuilder.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include "../model/Map3D.h"

namespace Initializer
{
	using namespace std;
	using namespace Model;

	const size_t default_potential_step = 3;

	MapBuilder::MapBuilder(coord_item_t length, coord_item_t width, coord_item_t height, unit_t unit)
		:boundary_(length, width, height),
		 unit_(unit),
		 potentialStep_(default_potential_step)
	{
	}

	MapBuilder::MapBuilder(const Coordinate& boundary, unit_t unit)
		: boundary_(boundary),
		  unit_(unit),
		  potentialStep_(default_potential_step)
	{
	}

	MapBuilder::MapBuilder(const string& cfg_file)
		:potentialStep_(default_potential_step)
	{
		load(cfg_file);
	}

	void MapBuilder::save(const string& filename)
	{
		return;
	}

	bool MapBuilder::load(const string& filename)
	{
		const string strLocation = "location";
		const string strBoundary = "boundary";
		const string strWind = "wind";
		const string strBuilding = "building";
		const string strUnit = "unit";
		const string strPotential = "potential";
		const string strOrigin = "origin";
		const string strIndex = "index";
		const string strCoord = "coordinate";

		using boost::property_tree::ptree;
		using boost::lexical_cast;

		ptree pt;
		read_json(filename, pt);

		unit_ = pt.get<unit_t>(strUnit);

		auto potentialNode = pt.get_optional<coord_item_t>(strPotential);
		if (potentialNode)
		{
			setLocalPotential(*potentialNode);
		}

		auto node_boundary = pt.get_child(strBoundary);
		transform(node_boundary.begin(), node_boundary.end(), boundary_.begin(), [](ptree::value_type& v)
		          {
			          return lexical_cast<coord_item_t>(v.second.data());
		          });

		auto node_location = pt.get_child_optional(strLocation);
		if (node_location)
		{
			setStartIndex(Coordinate());
			transform(node_location->begin(), node_location->end(), (*startIndex_).begin(), [](ptree::value_type& v)
			          {
				          return lexical_cast<coord_item_t>(v.second.data());
			          });
		}

		auto node_wind = pt.get_child_optional(strWind);
		if (node_wind)
		{
			setWind(WindVector());
			transform(node_wind->begin(), node_wind->end(), wind_->begin(), [](ptree::value_type& v)
			          {
				          return lexical_cast<wv_item_t>(v.second.data());
			          });
		}

		auto node_origin = pt.get_child_optional(strOrigin);
		if (node_origin)
		{
			auto node_index = node_origin->get_child(strIndex);
			Coordinate index;
			transform(node_index.begin(), node_index.end(), index.begin(), [](ptree::value_type& v)
			          {
				          return lexical_cast<coord_item_t>(v.second.data());
			          });

			auto node_coord = node_origin->get_child(strCoord);
			WindVector coord;
			transform(node_coord.begin(), node_coord.end(), coord.begin(), [](ptree::value_type& v)
			          {
				          return lexical_cast<wv_item_t>(v.second.data());
			          });

			setOrigin(make_pair(index, coord));
		}

		auto node_buildings = pt.get_child_optional(strBuilding);
		if (node_buildings)
		{
			for (auto node_building : *node_buildings)
			{
				auto node_bld_tree = node_building.second;

				stBuilding building;
				auto node_location = node_bld_tree.get_child(strLocation);
				transform(node_location.begin(), node_location.end(), building.location_.begin(), [](ptree::value_type& v)
				          {
					          return lexical_cast<coord_item_t>(v.second.data());
				          });

				auto node_boudnary = node_bld_tree.get_child(strBoundary);
				transform(node_boudnary.begin(), node_boudnary.end(), building.boundary_.begin(), [](ptree::value_type& v)
				          {
					          return lexical_cast<coord_item_t>(v.second.data());
				          });

				buildings_.push_back(building);
			}
		}

		return true;
	}

	MapBuilder* MapBuilder::setStartIndex(const Coordinate& startIndex)
	{
		startIndex_ = startIndex;
		return this;
	}

	MapBuilder* MapBuilder::setWind(const WindVector& wind)
	{
		wind_ = wind;
		return this;
	}

	MapBuilder* MapBuilder::setLocalPotential(coord_item_t step)
	{
		potentialStep_ = step;
		return this;
	}

	MapBuilder* MapBuilder::setBuildings(const vector<stBuilding>& buildings)
	{
		buildings_ = buildings;
		return this;
	}

	MapBuilder* MapBuilder::setOrigin(const boost::optional<pair<Coordinate, WindVector>>& origin)
	{
		origin_ = origin;
		return this;
	}

	shared_ptr<Map3D> MapBuilder::build()
	{
		const wv_item_t default_wind_norm = 1.618;

		shared_ptr<Map3D> map;

		if (startIndex_)
		{
			if (wind_)
			{
				map.reset(new Map3D(*startIndex_, boundary_, unit_, *wind_));
			}
			else
			{
				map.reset(new Map3D(*startIndex_, boundary_, unit_));
			}
		}
		else
		{
			if (wind_)
			{
				map.reset(new Map3D(boundary_[0], boundary_[1], boundary_[2], unit_, *wind_));
			}
			else
			{
				map.reset(new Map3D(boundary_[0], boundary_[1], boundary_[2], unit_));
			}
		}

		if (origin_)
		{
			map->setOrigin(*origin_);
		}

		auto wind_norm = default_wind_norm;
		if (wind_)
		{
			wind_norm = wind_->calcNorm();
		}

		for (auto bld : buildings_)
		{
			map->AddBuilding(bld.location_, bld.boundary_, potentialStep_, wind_norm);
		}

		return map;
	}
}