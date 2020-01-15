#pragma once

#include <memory>
#include "User.hpp"

namespace zia
{

    class Parser
    {
        public:
            static void parse(std::shared_ptr<zia::net::User> user, std::string text);
    };

}
