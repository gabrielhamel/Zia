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
#include "IClient.hpp"
#include "Request.hpp"

namespace net
{

    class NetworkManager
    {
        private:
            std::vector<boost::shared_ptr<net::IClient>> m_clients;
        public:
            NetworkManager();
            ~NetworkManager();
            void newClient(boost::shared_ptr<net::IClient> client);
            void removeClient(boost::shared_ptr<net::IClient> client);
            void recvData(boost::shared_ptr<net::IClient> client, const std::string &data);
    };

}
