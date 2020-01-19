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
#include "Client.hpp"

namespace zia
{

    class Parser
    {
        public:
            static void parse(std::shared_ptr<http::Client> client, std::string text);
    };

}
