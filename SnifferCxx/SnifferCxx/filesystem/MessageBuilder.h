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
    struct Leak;
}

namespace Filesystem {
    class Hypotheses_history;
    class Cell;
    class Map;

    
    class MessageBuilder {
    public:
        static std::shared_ptr<Filesystem::Hypotheses_history> buildMessage(const std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his);
        static std::shared_ptr<Filesystem::Map> buildMessage(const Model::Map3D & map);
        
    private:
        static bool buildCellMessage(const Model::Cell & cell, Filesystem::Cell * msg_cell);

	public:
		static std::unordered_map<Model::CellTag, CellTag, Model::enum_hash> Tag2Msg;
    };
}

#endif /* defined(__SnifferCxx__MessageBuilder__) */
