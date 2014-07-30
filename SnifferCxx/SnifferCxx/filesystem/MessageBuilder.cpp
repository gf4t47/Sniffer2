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

namespace Filesystem {
    using namespace std;

	unordered_map<Model::CellTag, Cell_CellTag, Model::enum_hash> MessageBuilder::Tag2Msg = { 
			{ Model::CellTag::Air,  Cell_CellTag::Cell_CellTag_Air}, 
			{ Model::CellTag::Building, Cell_CellTag::Cell_CellTag_Building }, 
			{ Model::CellTag::Ground, Cell_CellTag::Cell_CellTag_Ground } 
	};
    
    shared_ptr<Hypotheses_history> MessageBuilder::buildMessage(const std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his) {
		auto msg_hyps_his = make_shared<Hypotheses_history>();

		for (auto const & hyps : hyps_his) {
			auto msg_hyps = msg_hyps_his->add_hyps();
			for (auto const & hyp : *hyps) {
				auto msg_hyp = msg_hyps->add_hyp();
				msg_hyp->set_probability(hyp.getProbability());

				for (auto const & leak : hyp.getLeaks()) {
					auto msg_leak = msg_hyp->add_leak();
					msg_leak->set_concentration(leak.concentration_);

					auto msg_coord = new Coordinate();
					for (auto const & item : leak.location_) {
						msg_coord->add_coord_item(item);
					}
					msg_leak->set_allocated_location(msg_coord);
				}

				for (auto const & cells : hyp.getCelllsHistory()) {
					auto msg_cells = msg_hyp->add_methene_cells();

					for (auto const & cell_pair : *cells) {
						auto const & cell = cell_pair.second;

						//set cell tag
						auto msg_cell = msg_cells->add_cell();
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
					}
				}
			}
		}

		return msg_hyps_his;
    }
}