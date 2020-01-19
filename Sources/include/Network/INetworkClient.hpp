/**
 * @file INetworkClient.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief network client interface
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

    class INetworkClient
    {
        public:
            virtual ~INetworkClient() = default;
            virtual void send(const std::string &data) = 0;
            virtual std::size_t getId() const = 0;
    };

}
