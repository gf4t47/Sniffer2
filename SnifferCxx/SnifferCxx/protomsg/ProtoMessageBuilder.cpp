//
//  MessageBuilder.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/29/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "ProtoMessageBuilder.h"
#include "hypothesis.pb.h"
#include "dect.pb.h"
#include "../model/Hypotheses.h"
#include "../model/Cells.h"
#include "../model/Map3D.h"
#include "../model/Candidate.h"
#include "../initializer/DetectionInitializer.h"
#include "../support/MyLog.h"
#include <fstream>

namespace ProtoMsg {
    using namespace std;
	using namespace Support;

	unique_ptr<MyLog> ProtoMessageBuilder::lg_(make_unique<MyLog>());

	unordered_map<Model::CellTag, CellTag, Model::enum_hash> ProtoMessageBuilder::Tag2Msg = { 
			{ Model::CellTag::Air, CellTag::Air },
			{ Model::CellTag::Building, CellTag::Building },
			{ Model::CellTag::Ground, CellTag::Ground }
	};

	ProtoMessageBuilder::ProtoMessageBuilder(
		std::pair<std::string, std::shared_ptr<std::vector<std::shared_ptr<Model::Hypotheses>>>> mtn_info,
		std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> dect_info,
		std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> can_info,
		std::pair<std::string, std::shared_ptr<Model::Map3D>> map_info)
		:mtn_info_(mtn_info),
		dect_info_(dect_info),
		can_info_(can_info),
		map_info_(map_info) {
	}
    
    shared_ptr<Detections> ProtoMessageBuilder::buildMessage(const vector<Model::Detection> & detections) {
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
    
    shared_ptr<Map> ProtoMessageBuilder::buildMessage(const Model::Map3D & map) {
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
		auto msg_cells = msg_map->mutable_cells();
        for_each(map_ref.begin(), map_ref.end(), [&msg_cells](const Model::Cell & cell){auto msg_cell = msg_cells->add_cell(); buildCellMessage(cell, msg_cell);});
        
        return msg_map;
    }
    
    shared_ptr<Hypotheses_history> ProtoMessageBuilder::buildMessage(const vector<shared_ptr<Model::Hypotheses>> & hyps_his, size_t ideal_cells, bool only_detection /* = false*/) {
        double total_cells = 0.0;
		auto count_iteraton = 0;
        for (auto hyps : hyps_his) {
            for (auto const & hyp : *hyps) {
                for (auto i=0; i<hyp.getCelllsHistory().size(); i++) {
                    auto const & cells = hyp.getCelllsHistory()[i];
                    total_cells += cells->size();
                }
				count_iteraton += hyp.getCelllsHistory().size();
            }
        }
		BOOST_LOG_SEV(*lg_, severity_level::debug) << "total iterations in memory is " << count_iteraton;
        
        size_t cell_interval = round(total_cells / ideal_cells);
        
		auto msg_hyps_his = make_shared<Hypotheses_history>();

		auto count_output = 0;
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
                
				if (only_detection) {
					auto const cells = hyp.getMethaneCells();
					if (cells) {
						auto msg_cells = msg_hyp->add_methane_history();
						for (auto const & cell_pair : *cells) {
							auto const & cell = cell_pair.second;

							auto msg_cell = msg_cells->add_cell();
							buildCellMessage(cell, msg_cell);
						}
						count_output++;
					}
				}
				else {
					for (auto i = 0; i < hyp.getCelllsHistory().size(); i++) {
						if (cell_interval > 1 && i % cell_interval != 0) {
							continue;
						}

						auto const & cells = hyp.getCelllsHistory()[i];
						auto msg_cells = msg_hyp->add_methane_history();
						for (auto const & cell_pair : *cells) {
							auto const & cell = cell_pair.second;

							auto msg_cell = msg_cells->add_cell();
							buildCellMessage(cell, msg_cell);
						}
						count_output++;
					}
				}
			}
		}

		BOOST_LOG_SEV(*lg_, severity_level::debug) << "total iterations written into message is " << count_output;

		return msg_hyps_his;
    }
    
    bool ProtoMessageBuilder::buildCellMessage(const Model::Cell &cell, Cell * msg_cell) {
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
        msg_mtn->set_concentration(cell.getMethane().getParitcles());
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

	void ProtoMessageBuilder::WriteMsg(int ideal_cells, bool detection_only) {
		auto map_msg = buildMessage(*map_info_.second);
		fstream map_out(map_info_.first, ios::out | ios::trunc | ios::binary);
		if (!map_msg->SerializeToOstream(&map_out)) {
			BOOST_LOG_SEV(*lg_, severity_level::error) << "Failed to write map msg into " << map_info_.first;
		}
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Map message is written into " << map_info_.first;

		auto dect_msg = buildMessage(*dect_info_.second);
		fstream dect_out(dect_info_.first, ios::out | ios::trunc | ios::binary);
		if (!dect_msg->SerializeToOstream(&dect_out)) {
			BOOST_LOG_SEV(*lg_, severity_level::error) << "Failed to write detection msg into " << dect_info_.first;
		}
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Detection message is written into " << dect_info_.first;

		auto can_msg = buildMessage(*can_info_.second);
		fstream can_out(can_info_.first, ios::out | ios::trunc | ios::binary);
		if (!can_msg->SerializeToOstream(&can_out)) {
			BOOST_LOG_SEV(*lg_, severity_level::error) << "Failed to write candidates msg into " << can_info_.first;
		}
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Candidate message is written to file" << can_info_.first;

		auto mtn_msg = buildMessage(*mtn_info_.second, ideal_cells, detection_only);
		fstream mtn_out(mtn_info_.first, ios::out | ios::trunc | ios::binary);
		if (!mtn_msg->SerializeToOstream(&mtn_out)) {
			BOOST_LOG_SEV(*lg_, severity_level::error) << "Failed to write methane msg into " << mtn_info_.first;
		}
		BOOST_LOG_SEV(*lg_, severity_level::info) << "Methane message is written into " << mtn_info_.first;
	}
}