/**
 * @file User.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief An class to describe an http client
 * @version 1.0
 * @date 2020-01-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <boost/shared_ptr.hpp>
#include "INetworkClient.hpp"

namespace http
{

    class Client
    {
        private:
            boost::shared_ptr<zia::net::INetworkClient> m_networkPart;
        public:
            Client(boost::shared_ptr<zia::net::INetworkClient> networkPart);
            ~Client();
            boost::shared_ptr<zia::net::INetworkClient> getNetworkPart() const;
    };

}
