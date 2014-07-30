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
}

namespace Filesystem {
    class Hypotheses_history;
    
    class MessageBuilder {
    public:
        static std::shared_ptr<Filesystem::Hypotheses_history> buildMessage(const std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his);

	public:
		static std::unordered_map<Model::CellTag, Cell_CellTag, Model::enum_hash> Tag2Msg;
    };
}

#endif /* defined(__SnifferCxx__MessageBuilder__) */
