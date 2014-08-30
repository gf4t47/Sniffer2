//
//  MessageBuilder.h
//  SnifferCxx
//
//  Created by Ke Ding  on 7/29/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#ifndef __SnifferCxx__MessageBuilder__
#define __SnifferCxx__MessageBuilder__

#include <memory>
#include <vector>
#include "../model/Cell.h"
#include "../protomsg/cell.pb.h"

namespace Support {
	class MyLog;
}

namespace Model {
	class Hypotheses;
    class Map3D;
	struct Detection;
}

namespace ProtoMsg {
    class Hypotheses_history;
    class Detections;
    class Cell;
    class Map;
    
    class MessageBuilder {
    public:
		MessageBuilder(
			std::pair<std::string, const std::vector<std::shared_ptr<Model::Hypotheses>> &> mtn_info,
			std::pair<std::string, const std::vector<Model::Detection> &> dect_info,
			std::pair<std::string, const std::vector<Model::Detection> &> can_info,
			std::pair<std::string, const Model::Map3D &> map_info 
			);

        static std::shared_ptr<ProtoMsg::Hypotheses_history> buildMessage(const std::vector<std::shared_ptr<Model::Hypotheses>> & hyps_his, size_t ideal_cells, bool only_detection = false);
        static std::shared_ptr<ProtoMsg::Detections> buildMessage(const std::vector<Model::Detection> & detections);
        static std::shared_ptr<ProtoMsg::Map> buildMessage(const Model::Map3D & map);
        
    private:
        static bool buildCellMessage(const Model::Cell & cell, ProtoMsg::Cell * msg_cell);

	public:
		static std::unordered_map<Model::CellTag, CellTag, Model::enum_hash> Tag2Msg;
		void WriteMsg(int ideal_cells, bool detection_only);

	private:
		std::pair<std::string, const std::vector<std::shared_ptr<Model::Hypotheses>> &> mtn_info_;
		std::pair<std::string, const std::vector<Model::Detection> &> dect_info_;
		std::pair<std::string, const std::vector<Model::Detection> &> can_info_;
		std::pair<std::string, const Model::Map3D &> map_info_;

		static std::unique_ptr<Support::MyLog> lg_;
    };
}

#endif /* defined(__SnifferCxx__MessageBuilder__) */
