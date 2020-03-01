/**
 * @file Server.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2020-03-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <criterion/criterion.h>
#include "BoostNetworkServer.hpp"

const static std::string example =
    "domain: localhost\n"
    "listen:\n"
    "  port: 443\n"
    "  routes:\n"
    "    - name: ^\\/\n";

TestSuite(server);

Test(server, basic_creation)
{
    auto node = YAML::Load(example);
    auto host = core::config::Host(yconf::ConfigNode(node));
    net::INetworkServer *server = new net::BoostNetworkServer(0, host);
    delete server;
}
