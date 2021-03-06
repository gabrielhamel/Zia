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
#include <unordered_map>

#include "IClient.hpp"
#include "Configurations.hpp"
#include "ModuleApi.hpp"
#include "Module.hpp"

namespace net
{

    class NetworkManager
    {
        private:
            std::vector<boost::shared_ptr<net::IClient>> m_clients;
            const core::config::Host &m_configs;
            std::vector<std::pair<std::string, std::unique_ptr<Module>>> m_modulesListen; // name -> module
            std::vector<std::pair<std::regex, std::unique_ptr<Module>>> m_modulesRoutes; // routes -> module
            std::unique_ptr<Module> instanciateModule(const std::string &name) const;
            void sendBadRequest(net::IClient &client, std::string msg) const;
            void sendInternalError(net::IClient &client, std::string msg) const;
            void responseError(int status, std::string message, http::IResponse &response) const;

        public:
            NetworkManager(const core::config::Host &configs);
            ~NetworkManager();
            void newClient(boost::shared_ptr<net::IClient> client);
            void removeClient(boost::shared_ptr<net::IClient> client);
            void recvData(boost::shared_ptr<net::IClient> client, std::string &data);
    };

}
