/**
 * @file Host.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-25
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CONFHOST_HPP
#define CONFHOST_HPP

#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "Route.hpp"

namespace core::config
{

class Host : public ModulesContainer
{

private:

    std::string m_domain;

    std::uint16_t m_port;

    std::vector<core::config::Route> m_routes;

public:

    Host(const IConfigNode &node);

    ~Host();

    std::string getDomain() const;

    std::uint16_t getPort() const;

    bool isRouteMatch(const std::string uri) const;

    const core::config::Route &getRouteByMatch(const std::string &uri) const;

    const core::config::Route &getRouteByName(const std::string &name) const;

};

} // namespace core::config

#endif // CONFHOST_HPP
