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
#include "cell.pb.h"

namespace Model {
    class Hypothesis;
    class Map3D;
    class Cell;
}

namespace Initializer {
    struct Detection;
}

namespace Msg {
    class Hypotheses_history;
    class Detections;
    class Cell;
    class Map;
    
    class MessageBuilder {
    public:
        static std::shared_ptr<Msg::Hypotheses_history> buildMessage(const std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his, size_t ideal_cells);
        static std::shared_ptr<Msg::Detections> buildMessage(const std::vector<Initializer::Detection> & detections);
        static std::shared_ptr<Msg::Map> buildMessage(const Model::Map3D & map);
        
    private:
        static bool buildCellMessage(const Model::Cell & cell, Msg::Cell * msg_cell);

	public:
		static std::unordered_map<Model::CellTag, CellTag, Model::enum_hash> Tag2Msg;
    };
}

#endif /* defined(__SnifferCxx__MessageBuilder__) */
