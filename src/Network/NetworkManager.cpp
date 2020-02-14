/**
 * @file NetworkManager.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-02-11
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>

#include "NetworkManager.hpp"
#include "Module.hpp"
#include "Configurations.hpp"

net::NetworkManager::NetworkManager(const core::config::Host &configs) :
m_configs(configs)
{
    // setConfigurations
    const auto modules = configs.getModules();
    for (const auto &module : modules) {
        //Module(core::Configurations::modulesPath + "/")
        // Create and insert module
        // Configure it
    }
    // For in routes
    // find modules
    // insert it and configure it

    auto res = core::Configurations::getAllDynName();
    for (auto file : res) {
        std::cout << file << std::endl;
    }

    // TODO
}

net::NetworkManager::~NetworkManager()
{

}

void net::NetworkManager::newClient(boost::shared_ptr<net::IClient> client)
{
    // newConnection
    for (const auto &module : this->m_modulesListen)
        module.second->newConnection(*client);
    for (const auto &module : this->m_modulesRoutes)
        module.second->newConnection(*client);
}

void net::NetworkManager::removeClient(boost::shared_ptr<IClient> client)
{
    // disconnection
    for (const auto &module : this->m_modulesListen)
        module.second->disconnection(*client);
    for (const auto &module : this->m_modulesRoutes)
        module.second->disconnection(*client);
}

void net::NetworkManager::recvData(boost::shared_ptr<net::IClient> client, const std::string &data)
{
    // afterReceive
    // afterUnpacked
    // execute
    // beforePacked
    // beforeSend
    // TODO
}
