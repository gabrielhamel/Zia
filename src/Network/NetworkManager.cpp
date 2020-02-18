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
#include "Configurations.hpp"

net::NetworkManager::NetworkManager(const core::config::Host &configs) :
m_configs(configs)
{
    const auto modules = configs.getModules();
    for (const auto &module : modules) {
        auto tmp = std::pair<std::string, std::unique_ptr<Module>>(module.first, std::move(instanciateModule(module.first)));
        this->m_modulesListen.push_back(std::move(tmp));
        this->m_modulesListen.back().second->get().setConfigurations(module.second.getConfigs());
    }
    for (const auto &route : configs.getRoutes())
        for (const auto &module : route.getModules()) {
            auto tmp = std::pair<std::regex, std::unique_ptr<Module>>(route.getPattern(), std::move(instanciateModule(module.first)));
            this->m_modulesRoutes.push_back(std::move(tmp));
            this->m_modulesRoutes.back().second->get().setConfigurations(module.second.getConfigs());
        }
}

std::unique_ptr<Module> net::NetworkManager::instanciateModule(const std::string &name) const
{
    for (auto file : core::Configurations::getAllDynName()) {
        auto ptr = std::make_unique<Module>(file);
        if (ptr->get().name() == name)
            return std::move(ptr);
    }
    throw std::runtime_error("Module " + name + " doesn't exists");
}

net::NetworkManager::~NetworkManager()
{

}

void net::NetworkManager::newClient(boost::shared_ptr<net::IClient> client)
{
    for (const auto &module : this->m_modulesListen)
        module.second->get().newConnection(*client);
    for (const auto &module : this->m_modulesRoutes)
        module.second->get().newConnection(*client);
}

void net::NetworkManager::removeClient(boost::shared_ptr<IClient> client)
{
    for (const auto &module : this->m_modulesListen)
        module.second->get().disconnection(*client);
    for (const auto &module : this->m_modulesRoutes)
        module.second->get().disconnection(*client);
}

void net::NetworkManager::recvData(boost::shared_ptr<net::IClient> client, const std::string &data)
{
    // TODO
    // afterReceive
    // afterUnpacked
    // execute
    // beforePacked
    // beforeSend
}
