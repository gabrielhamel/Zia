/**
 * @file Host.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-31
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Host.hpp"

core::config::Host::Host(const IConfigNode &node)
{
    this->m_domain = node.getValue("domain");
    auto listen = node.getChild("listen");
    this->m_port = std::stoi(listen->getValue("port"));
    try {
        auto modules = listen->getNodeArray("modules");
        for (const auto &module : modules)
            this->addModule(*module);
    } catch (...) {

    }
    auto routes = listen->getNodeArray("routes");
    if (routes.size() == 0)
        throw std::runtime_error("There should be at least one route");
    for (const auto &route : routes)
        this->m_routes.push_back(*route);
}

core::config::Host::~Host()
{

}

std::string core::config::Host::getDomain() const
{
    return this->m_domain;
}

std::uint16_t core::config::Host::getPort() const
{
    return this->m_port;
}

bool core::config::Host::isRouteMatch(const std::string uri) const
{
    for (const auto &route : this->m_routes)
        if (std::regex_search(uri, route.getPattern()))
            return true;
    return false;
}

const core::config::Route &core::config::Host::getRouteByMatch(const std::string &uri) const
{
    for (auto &route : this->m_routes)
        if (this->isRouteMatch(uri))
            return route;
    throw std::runtime_error("Unable to find one route");
}

const core::config::Route &core::config::Host::getRouteByName(const std::string &name) const
{
    for (auto &route : this->m_routes)
        if (route.getName() == name)
            return route;
    throw std::runtime_error("Unable to find that route");
}

const std::vector<core::config::Route> &core::config::Host::getRoutes() const
{
    return this->m_routes;
}
