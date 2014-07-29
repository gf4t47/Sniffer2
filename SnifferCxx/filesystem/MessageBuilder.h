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
namespace Model {
    class Hypothesis;
}

namespace Filesystem {
    class Hypotheese_history;
    
    class MessageBuilder {
    public:
        static std::shared_ptr<Hypotheese_history> buildMessage(const std::vector<std::shared_ptr<std::vector<Model::Hypothesis>>> & hyps_his);
    };
}

#endif /* defined(__SnifferCxx__MessageBuilder__) */
