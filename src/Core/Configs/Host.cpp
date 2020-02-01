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
// - domain: subdomain.example.com
//     listen:
//       port: 443
//       modules:
//         - name: tls
//           configs: # Configs passés au constructeur du module
//             certificate: '/etc/zia/public_key.pem'
//       routes:
//         - name: ^/*.php$
//           modules:
//             - name: php-module
//               configs: # Configs intermédiaires passés lors du call de la fonction execute du module
//                 host: localhost
//                 port: 9000
//         - name: /
//           modules:
//             - name: file
//               configs:
//                 root: /var/www/
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
