//
//  MessageBuilder.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/29/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "MessageBuilder.h"
#include "hypothesis.pb.h"
#include "dect.pb.h"
#include "../model/Hypothesis.h"
#include "../model/Cells.h"
#include "../model/Map3D.h"
#include "../model/Candidate.h"
#include "../initializer/DetectionInitializer.h"

namespace ProtoMsg {
    using namespace std;

	unordered_map<Model::CellTag, CellTag, Model::enum_hash> MessageBuilder::Tag2Msg = { 
			{ Model::CellTag::Air, CellTag::Air },
			{ Model::CellTag::Building, CellTag::Building },
			{ Model::CellTag::Ground, CellTag::Ground }
	};
    
    shared_ptr<Detections> MessageBuilder::buildMessage(const vector<Initializer::Detection> & detections) {
        auto msg_dects = make_shared<Detections>();
        
        for (auto detection : detections) {
            auto msg_dect = msg_dects->add_dect();
            msg_dect->set_time(detection.time_);
            for (auto leak : detection.detected_) {
                auto msg_leak = msg_dect->add_leak();
                
                msg_leak->set_concentration(leak.concentration_);
                
//                auto msg_coord = new Coordinate();
                auto msg_coord = msg_leak->mutable_location();
				msg_coord->set_coord_x(leak.location_[0]);
				msg_coord->set_coord_y(leak.location_[1]);
				msg_coord->set_coord_z(leak.location_[2]);
//                msg_leak->set_allocated_location(msg_coord);
            }
        }
        
        return msg_dects;
    }
    
    shared_ptr<Map> MessageBuilder::buildMessage(const Model::Map3D & map) {
        auto msg_map = make_shared<Map>();
        
//        auto msg_startIndex = new Coordinate();
        auto msg_startIndex = msg_map->mutable_startindex();
        auto startIndex = map.getStartIndex();
		msg_startIndex->set_coord_x(*startIndex);
		msg_startIndex->set_coord_y(*(startIndex + 1));
		msg_startIndex->set_coord_z(*(startIndex + 2));
//        msg_map->set_allocated_startindex(msg_startIndex);
        
//        auto msg_boundary = new Coordinate();
        auto msg_boundary = msg_map->mutable_boundary();
        auto boudary = map.getBoundary();
		msg_boundary->set_coord_x(*boudary);
		msg_boundary->set_coord_y(*(boudary + 1));
		msg_boundary->set_coord_z(*(boudary + 2));
//        msg_map->set_allocated_boundary(msg_boundary);
        
        boost::const_multi_array_ref<Model::Cell, 1> map_ref(map.data(), boost::extents[map.num_elements()]);
        for_each(map_ref.begin(), map_ref.end(), [&msg_map](const Model::Cell & cell){auto msg_cell = msg_map->add_cell(); buildCellMessage(cell, msg_cell);});
        
        return msg_map;
    }
    
    shared_ptr<Hypotheses_history> MessageBuilder::buildMessage(const vector<shared_ptr<vector<Model::Hypothesis>>> & hyps_his, size_t ideal_cells) {
        double total_cells = 0.0;
        for (auto hyps : hyps_his) {
            for (auto const & hyp : *hyps) {
                for (auto i=0; i<hyp.getCelllsHistory().size(); i++) {
                    auto const & cells = hyp.getCelllsHistory()[i];
                    total_cells += cells->size();
                }
            }
        }
        
        size_t cell_interval = round(total_cells / ideal_cells);
        
		auto msg_hyps_his = make_shared<Hypotheses_history>();

		for (auto hyps : hyps_his) {
			auto msg_hyps = msg_hyps_his->add_hyps();
			for (auto const & hyp : *hyps) {               
                auto msg_hyp = msg_hyps->add_hyp();
                
                msg_hyp->set_probability(hyp.getProbability());
                
                for (auto const & leak : hyp.getLeaks()) {
                    auto msg_leak = msg_hyp->add_leak();
                    msg_leak->set_concentration(leak.concentration_);
                    
//                    auto msg_coord = new Coordinate();
                    auto msg_coord = msg_leak->mutable_location();
					msg_coord->set_coord_x(leak.location_[0]);
					msg_coord->set_coord_y(leak.location_[1]);
					msg_coord->set_coord_z(leak.location_[2]);
//                    msg_leak->set_allocated_location(msg_coord);
                }
                
                for (auto i = 0; i < hyp.getCelllsHistory().size(); i++) {
                    auto const & cells = hyp.getCelllsHistory()[i];
                    if (cell_interval > 1 && i % cell_interval != 0) {
                        continue;
                    }
                    
                    auto msg_cells = msg_hyp->add_methene_cells();
                    
                    for (auto const & cell_pair : *cells) {
                        auto const & cell = cell_pair.second;
                        
                        auto msg_cell = msg_cells->add_cell();
                        buildCellMessage(cell, msg_cell);
                    }
                }
			}
		}

		return msg_hyps_his;
    }
    
    bool MessageBuilder::buildCellMessage(const Model::Cell &cell, Cell * msg_cell) {
        //set cell tag
        msg_cell->set_tag(Tag2Msg[cell.getTag()]);
        
        //set cell coordinate
//        auto msg_coord = new Coordinate();
        auto msg_coord = msg_cell->mutable_coord();
		auto const & coord = cell.getCoordinate();
		msg_coord->set_coord_x(coord[0]);
		msg_coord->set_coord_y(coord[1]);
		msg_coord->set_coord_z(coord[2]);
//        msg_cell->set_allocated_coord(msg_coord);
        
        //set cell methane
//        auto msg_mtn = new Cell::Methane();
        auto msg_mtn = msg_cell->mutable_mtn();
        msg_mtn->set_concentration(cell.getMethane().getConcentration());
//        msg_cell->set_allocated_mtn(msg_mtn);
        
        //set cell wind
//        auto msg_wind = new Cell::Wind();
        auto msg_wind = msg_cell->mutable_wind();
        
//        auto msg_windvector = new Cell::WindVector();
        auto msg_windvector = msg_wind->mutable_wind();
		auto const & wv = cell.getWind().getWV();
		msg_windvector->set_wv_x(wv[0]);
		msg_windvector->set_wv_y(wv[1]);
		msg_windvector->set_wv_z(wv[2]);
//        msg_wind->set_allocated_wind(msg_windvector);
        
//        auto msg_potential = new Cell::WindVector();
        auto msg_potential = msg_wind->mutable_potential();
		auto const & pt = cell.getWind().getPotential();
		msg_potential->set_wv_x(pt[0]);
		msg_potential->set_wv_y(pt[1]);
		msg_potential->set_wv_z(pt[2]);
//        msg_wind->set_allocated_potential(msg_potential);
        
//        msg_cell->set_allocated_wind(msg_wind);
        
        return true;
    }
}