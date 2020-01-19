/**
 * @file Parser.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief Parser of http request receive by networkManager
 * @version 1.0
 * @date 2020-01-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <memory>
#include "IClient.hpp"

namespace http
{

    class Parser
    {
        public:
            static void parse(net::IClient &client, std::string data);
    };

}
