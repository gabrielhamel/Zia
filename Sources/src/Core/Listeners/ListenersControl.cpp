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

core::ListenersControl::ListenersControl()
{

}

core::ListenersControl::~ListenersControl()
{

}

void core::ListenersControl::addListeners(unsigned short port)
{
    net::BoostNetworkServer *server;
    try {
        server = new net::BoostNetworkServer(port);
        this->m_threads.emplace(port, std::make_unique<std::thread>(&net::BoostNetworkServer::run, server));
        this->m_listeners.emplace(port, server);
    }
    catch (std::exception &e) {
        throw e;
    }
}

std::vector<unsigned short> core::ListenersControl::listListeners() const
{
    std::vector<unsigned short> res;
    for (auto &key : this->m_listeners)
        res.push_back(key.first);
    return res;
}
