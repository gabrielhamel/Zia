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

#include <criterion/criterion.h>
#include <iostream>
#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "Host.hpp"

const static std::string example =
    "domain: subdomain.example.com\n"
    "listen:\n"
    "  port: 443\n"
    "  modules:\n"
    "    - name: tls\n"
    "    - name: php\n"
    "  routes:\n"
    "    - name: ^\\/.+\\.php$\n"
    "    - name: ^\\/\n";

Test(HostConf, domain)
{
    auto node = YAML::Load(example);
    auto host = core::config::Host(yconf::ConfigNode(node));

    cr_assert_eq(host.getDomain(), "subdomain.example.com");
}

Test(HostConf, port)
{
    auto node = YAML::Load(example);
    auto host = core::config::Host(yconf::ConfigNode(node));

    cr_assert_eq(host.getPort(), 443);
}

Test(HostConf, modules)
{
    auto node = YAML::Load(example);
    auto host = core::config::Host(yconf::ConfigNode(node));

    cr_assert_eq(host.hasModule("tls"), true);
    cr_assert_eq(host.hasModule("issou"), false);
}

Test(HostConf, routeByName)
{
    auto node = YAML::Load(example);
    auto host = core::config::Host(yconf::ConfigNode(node));

    cr_assert_eq(host.getRouteByName("^\\/").getName(), "^\\/");
    cr_assert_eq(host.getRouteByName("^\\/.+\\.php$").getName(), "^\\/.+\\.php$");
}

Test(HostConf, routeMatch)
{
    auto node = YAML::Load(example);
    auto host = core::config::Host(yconf::ConfigNode(node));

    cr_assert_eq(host.isRouteMatch("/index"), true);
    cr_assert_eq(host.isRouteMatch("index"), false);
}

Test(HostConf, getModules)
{
    auto node = YAML::Load(example);
    auto host = core::config::Host(yconf::ConfigNode(node));

    auto modules = host.getModulesName();
    cr_assert_neq(std::find(modules.begin(), modules.end(), "php"), modules.end());
    cr_assert_neq(std::find(modules.begin(), modules.end(), "tls"), modules.end());
    auto module = host.getModule("tls");
    cr_assert_eq(module.getName(), "tls");
}

Test(HostConf, getRouteByMatch)
{
    auto node = YAML::Load(example);
    auto host = core::config::Host(yconf::ConfigNode(node));

    cr_assert_eq(host.getRouteByMatch("/index").getName(), "^\\/.+\\.php$");
}
