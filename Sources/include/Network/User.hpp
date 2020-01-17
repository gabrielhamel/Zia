/**
 * @file User.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief An class to describe an user
 * @version 1.0
 * @date 2020-01-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <boost/shared_ptr.hpp>
#include "INetworkClient.hpp"

namespace zia::net
{

    class User
    {
        private:
            boost::shared_ptr<zia::net::INetworkClient> m_networkPart;
        public:
            User(boost::shared_ptr<zia::net::INetworkClient> networkPart);
            ~User();
            boost::shared_ptr<zia::net::INetworkClient> getNetworkPart() const;
    };

}
