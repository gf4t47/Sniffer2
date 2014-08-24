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

namespace Model {
    class Hypothesis;
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
        static std::shared_ptr<ProtoMsg::Hypotheses_history> buildMessage(const std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his, size_t ideal_cells);
        static std::shared_ptr<ProtoMsg::Detections> buildMessage(const std::vector<Model::Detection> & detections);
        static std::shared_ptr<ProtoMsg::Map> buildMessage(const Model::Map3D & map);
        
    private:
        static bool buildCellMessage(const Model::Cell & cell, ProtoMsg::Cell * msg_cell);

	public:
		static std::unordered_map<Model::CellTag, CellTag, Model::enum_hash> Tag2Msg;
    };
}

#endif /* defined(__SnifferCxx__MessageBuilder__) */
