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
#include "BoostNetworkServer.hpp"

namespace core {

class ListenersControl
{

private:

    std::map<unsigned short, net::BoostNetworkServer *> m_listeners;
    std::map<unsigned short, std::unique_ptr<std::thread>> m_threads;

public:

    ListenersControl();

    void addListeners(unsigned short port);

    ~ListenersControl();

};

} // namespace core

#endif // LISTENERS_CONTROL_HPP
