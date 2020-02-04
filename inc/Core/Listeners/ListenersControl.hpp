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

#ifndef LISTENERS_CONTROL_HPP
#define LISTENERS_CONTROL_HPP

#include <thread>
#include <memory>
#include <map>
#include "Configurations.hpp"
#include "BoostNetworkServer.hpp"

namespace core {

class ListenersControl
{

private:

    std::map<unsigned short, std::shared_ptr<net::BoostNetworkServer>> m_listeners;

    std::map<unsigned short, std::thread> m_threads;

    core::Configurations &m_configs;

public:

    ListenersControl(core::Configurations &configs);

    ~ListenersControl();

    void newListener(unsigned short port);

    void destroyListener(unsigned short port);

    std::vector<unsigned short> listListeners() const;

    core::Configurations &getConfigurations() const;

    void reload();

};

} // namespace core

#endif // LISTENERS_CONTROL_HPP
