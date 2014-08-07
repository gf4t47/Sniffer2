//
//  MessageBuilder.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/29/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "MessageBuilder.h"
#include "hypothesis.pb.h"
#include "../model/Hypothesis.h"
#include "../model/Cells.h"
#include "../model/Map3D.h"

namespace Filesystem {
    using namespace std;

	unordered_map<Model::CellTag, CellTag, Model::enum_hash> MessageBuilder::Tag2Msg = { 
			{ Model::CellTag::Air, CellTag::Air },
			{ Model::CellTag::Building, CellTag::Building },
			{ Model::CellTag::Ground, CellTag::Ground }
	};
    
    shared_ptr<Map> MessageBuilder::buildMessage(const Model::Map3D & map) {
        auto msg_map = make_shared<Map>();
        
        auto msg_startIndex = new Coordinate();
        auto startIndex = map.getStartIndex();
        for (int i = 0; i < 3; i++) {
            msg_startIndex->add_coord_item(*startIndex++);
        }
        msg_map->set_allocated_startindex(msg_startIndex);
        
        auto msg_boudary = new Coordinate();
        auto boudary = map.getBoundary();
        for (int i = 0; i < 3; i++) {
            msg_boudary->add_coord_item(*boudary++);
        }
        msg_map->set_allocated_boundary(msg_boudary);
        
        boost::const_multi_array_ref<Model::Cell, 1> map_ref(map.data(), boost::extents[map.num_elements()]);
        for_each(map_ref.begin(), map_ref.end(), [&msg_map](const Model::Cell & cell){auto msg_cell = msg_map->add_cell(); buildCellMessage(cell, msg_cell);});
        
        return msg_map;
    }
    
    shared_ptr<Hypotheses_history> MessageBuilder::buildMessage(const vector<shared_ptr<vector<Model::Hypothesis>>> & hyps_his) {
        const double ideal_cells = 500000;
        
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
                
                for (auto const & prob : hyp.getProbabilityHistory()) {
                    auto msg_prob = msg_hyp->add_probability();
                    msg_prob->set_index(prob.first);
                    msg_prob->set_prob(prob.second);
                }
                
                for (auto const & leak : hyp.getLeaks()) {
                    auto msg_leak = msg_hyp->add_leak();
                    msg_leak->set_concentration(leak.concentration_);
                    
                    auto msg_coord = new Coordinate();
                    for (auto const & item : leak.location_) {
                        msg_coord->add_coord_item(item);
                    }
                    msg_leak->set_allocated_location(msg_coord);
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
        auto msg_coord = new Coordinate();
        for (auto const & item : cell.getCoordinate()) {
            msg_coord->add_coord_item(item);
        }
        msg_cell->set_allocated_coord(msg_coord);
        
        //set cell methane
        auto msg_mtn = new Cell::Methane();
        msg_mtn->set_concentration(cell.getMethane().getParticleNum());
        msg_cell->set_allocated_mtn(msg_mtn);
        
        //set cell wind
        auto msg_wind = new Cell::Wind();
        
        auto msg_windvector = new Cell::WindVector();
        for (auto const & item : cell.getWind().getWV()) {
            msg_windvector->add_wv_item(item);
        }
        msg_wind->set_allocated_wind(msg_windvector);
        
        auto msg_potential = new Cell::WindVector();
        for (auto const & item : cell.getWind().getPotential()) {
            msg_potential->add_wv_item(item);
        }
        msg_wind->set_allocated_potential(msg_potential);
        
        msg_cell->set_allocated_wind(msg_wind);
        
        return true;
    }
}