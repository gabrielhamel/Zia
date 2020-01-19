/**
 * @file INetworkServer.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief server interface
 * @version 1.0
 * @date 2020-01-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <string>

namespace net
{

    class INetworkServer
    {
        public:
            virtual ~INetworkServer() = default;
            virtual void run() = 0;
    };

}
