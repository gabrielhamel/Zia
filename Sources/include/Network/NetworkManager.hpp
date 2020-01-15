/**
 * @file NetworkManager.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief Class to interract with network part and worker
 * @version 1.0
 * @date 2020-01-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "User.hpp"
#include "Parser.hpp"

namespace zia::net
{

    class NetworkManager
    {
        private:
            std::vector<std::shared_ptr<zia::net::User>> m_clients;
        public:
            NetworkManager();
            ~NetworkManager();
            void newClient(boost::shared_ptr<zia::net::INetworkClient> client);
            void removeClient(boost::shared_ptr<zia::net::INetworkClient> client);
            void recvData(boost::shared_ptr<zia::net::INetworkClient> client, const std::string data);
    };

}
