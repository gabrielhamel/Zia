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

struct IClient
{

    /**
     * @brief Default destructor
     *
     */
    virtual ~IClient() = default;

    /**
     * @brief Send 'data' into a tcp packet to the client
     *
     * Return true if there are no problems
     */
    virtual bool send(const std::string &data) = 0;

    /**
     * @brief Gets an unique ID on the client
     *
     */
    virtual std::size_t getId() const noexcept = 0;

};

}
