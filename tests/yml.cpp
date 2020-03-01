/**
 * @file yml.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2020-03-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <criterion/criterion.h>
#include "Redirector.hpp"
#include <iostream>
#include "yconf/ConfigNode.hpp"
#include "Configurations.hpp"

#ifndef _WIN32
    const std::string path("example/config.linux.yml");
#else
    const std::string path("example\\config.windows.yml");
#endif

TestSuite(yml);

Test(yml, basic_loading)
{
    std::unique_ptr<IConfigNode> file = std::make_unique<yconf::ConfigNode>(path);
}

Test(yml, depth_child)
{
    const std::string example =
    "    configs:\n"
    "      host:\n"
    "        value: localhost\n";
    auto node = YAML::Load(example);
    cr_assert_eq(yconf::ConfigNode(node).getChild("configs.host")->getValue("value"), "localhost");
}

Test(yml, invalid_child)
{
    bool ok = false;
    const std::string example =
    "    configs:\n"
    "      host:\n"
    "        value: localhost\n";
    auto node = YAML::Load(example);
    try {
        yconf::ConfigNode(node).getChild("configs.issou");
    }
    catch (const std::exception &e) {
        cr_assert_eq(std::string(e.what()), "No such child node 'issou'");
        ok = true;
    }
    cr_assert_eq(ok, true);
}

Test(yml, getScalarArray)
{
    const std::string example =
    "routes:\n"
    "  - one\n"
    "  - two\n";
    auto node = YAML::Load(example);
    auto array = yconf::ConfigNode(node).getScalarArray("routes");

    cr_assert_neq(std::find(array.begin(), array.end(), "one"), array.end());
    cr_assert_neq(std::find(array.begin(), array.end(), "two"), array.end());
}

Test(yml, noscalar)
{
    auto node = YAML::Load(path);
    bool ok = false;
    try {
        yconf::ConfigNode(node).getAllScalarsOf("hosts");
    }
    catch (const std::exception &e) {
        ok = true;
        cr_assert_eq(std::string(e.what()), "No such property 'hosts'");
    }
    cr_assert_eq(ok, true);
}

Test(yml, globalConfigs)
{
    core::Configurations configs(path);
    Redirector redirect(std::cout);
    configs.print();
}

Test(yml, getHostByDomain)
{
    core::Configurations configs(path);

    cr_assert_eq(configs.getHostByDomain("localhost").getDomain(), "localhost");
    cr_assert_eq(configs.getHostByPort(configs.getHostByDomain("localhost").getPort()).getDomain(), "localhost");
}

Test(yml, dynNames)
{
    core::Configurations configs(path);
    auto dyn = configs.getAllDynName();
}
