/**
 * @file RouteConf.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-29
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <criterion/criterion.h>
#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "Route.hpp"

const static std::string example =
    "name: \\/index\n"
    "modules:\n"
    "  - name: php\n"
    "    configs:\n"
    "      host: localhost\n"
    "      port: 9000\n"
    "  - name: tls\n"
    "    configs:\n"
    "      certificate: true\n"
    "      path: issou\n";

Test(RouteConf, name)
{
    auto node = YAML::Load(example);
    auto route = core::config::Route(yconf::ConfigNode(node), "/etc/zia/module.d");

    cr_assert_eq(route.getName(), "\\/index");
}

Test(RouteConf, pattern)
{
    auto node = YAML::Load(example);
    auto route = core::config::Route(yconf::ConfigNode(node), "/etc/zia/module.d");

    cr_assert_eq(std::regex_search("/index", route.getPattern()), true);
    cr_assert_eq(std::regex_search("/index/issou", route.getPattern()), true);
    cr_assert_eq(std::regex_search("/lol/inde", route.getPattern()), false);
}
