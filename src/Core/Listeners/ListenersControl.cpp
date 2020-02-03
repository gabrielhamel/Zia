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

#include "ListenersControl.hpp"

core::ListenersControl::ListenersControl(core::Configurations &configs) :
m_configs(configs)
{
    this->reload();
}

core::ListenersControl::~ListenersControl()
{
    for (auto &elem : this->m_listeners)
        if (elem.second != nullptr)
            this->destroyListener(elem.first);
}

void core::ListenersControl::newListener(unsigned short port)
{
    net::BoostNetworkServer *server;
    try {
        server = new net::BoostNetworkServer(port, m_configs);
        this->m_threads.emplace(port, std::make_unique<std::thread>(&net::BoostNetworkServer::run, server));
        this->m_listeners.emplace(port, server);
    }
    catch (std::exception &e) {
        throw e;
    }
}

void core::ListenersControl::destroyListener(unsigned short port)
{
    this->m_listeners[port]->stop();
    this->m_threads[port]->join();
    this->m_listeners[port] = nullptr;
}

std::vector<unsigned short> core::ListenersControl::listListeners() const
{
    std::vector<unsigned short> res;
    for (auto &key : this->m_listeners) {
        if (key.second != nullptr)
            res.push_back(key.first);
    }
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
        if (elem.second != nullptr)
            this->destroyListener(elem.first);
}
