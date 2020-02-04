/**
 * @file ListenersControl.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-23
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>
#include "ListenersControl.hpp"

core::ListenersControl::ListenersControl(core::Configurations &configs) :
m_configs(configs)
{
    this->reload();
}

core::ListenersControl::~ListenersControl()
{
    for (auto &elem : this->m_listeners)
        this->destroyListener(elem.first);
}

void core::ListenersControl::newListener(unsigned short port)
{
    this->m_listeners.emplace(port, std::make_unique<net::BoostNetworkServer>(port, m_configs));
    this->m_threads.emplace(port, std::thread(&net::BoostNetworkServer::run, this->m_listeners[port].get()));

}

void core::ListenersControl::destroyListener(unsigned short port)
{
    this->m_listeners[port]->stop();
    this->m_threads[port].join();
}

std::vector<unsigned short> core::ListenersControl::listListeners() const
{
    std::vector<unsigned short> res;
    for (auto &key : this->m_listeners)
        if (key.second != nullptr)
            res.push_back(key.first);
    return res;
}

core::Configurations &core::ListenersControl::getConfigurations() const
{
    return this->m_configs;
}

void core::ListenersControl::reload()
{
    // Delete all listeners
    for (auto &elem : this->m_listeners)
        this->destroyListener(elem.first);
    this->m_listeners.clear();
    this->m_threads.clear();

    // Read config and launch threads
    this->m_configs.reload();
    const auto &hosts = this->m_configs.getHosts();
    for (const auto &host : hosts)
        this->newListener(host.getPort());
}
