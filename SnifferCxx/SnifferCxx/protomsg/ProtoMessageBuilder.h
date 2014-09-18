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

namespace Support
{
	class MyLog;
}

namespace Model
{
	class Hypotheses;
	class Map3D;
	struct Detection;
}

namespace ProtoMsg
{
	class Hypotheses_history;
	class Detections;
	class Map;

	class ProtoMessageBuilder
	{
	public:
		ProtoMessageBuilder(
			std::pair<std::string, std::shared_ptr<std::vector<std::shared_ptr<Model::Hypotheses>>>> mtn_info,
			std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> dect_info,
			std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> can_info,
			std::pair<std::string, std::shared_ptr<Model::Map3D>> map_info
		);

		static std::shared_ptr<Hypotheses_history> buildMessage(const std::vector<std::shared_ptr<Model::Hypotheses>>& hyps_his, size_t ideal_cells, bool only_detection = false);
		static std::shared_ptr<Detections> buildMessage(const std::vector<Model::Detection>& detections);
		static std::shared_ptr<Map> buildMessage(const Model::Map3D& map);
		static std::unordered_map<Model::CellTag, CellTag, Model::enum_hash> Tag2Msg;
		void WriteMsg(int ideal_cells, bool detection_only);

	private:
		static bool buildCellMessage(const Model::Cell& cell, Cell* msg_cell);

	private:
		std::pair<std::string, std::shared_ptr<std::vector<std::shared_ptr<Model::Hypotheses>>>> mtn_info_;
		std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> dect_info_;
		std::pair<std::string, std::shared_ptr<std::vector<Model::Detection>>> can_info_;
		std::pair<std::string, std::shared_ptr<Model::Map3D>> map_info_;

		static std::unique_ptr<Support::MyLog> lg_;
	};
}

#endif /* defined(__SnifferCxx__MessageBuilder__) */