/**
 * @file HttpResponse.cpp
 * @author Loïc Bontemps (loic1.bontemps@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-27
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <criterion/criterion.h>
#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "Module.hpp"

const static std::string example =
    "name: php-module\n"
    "configs:\n"
    "  host: localhost\n"
    "  port: 9000\n";

Test(ModuleConf, name)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(std::make_unique<yconf::ConfigNode>(node), "/etc/zia/module.d");

    cr_assert_eq(module.getName(), "php-module");
}

Test(ModuleConf, defaultPath)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(std::make_unique<yconf::ConfigNode>(node), "/etc/zia/module.d");

    cr_assert_eq(module.getDefaultPath(), "/etc/zia/module.d");
}

Test(ModuleConf, hasConfig)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(std::make_unique<yconf::ConfigNode>(node), "/etc/zia/module.d");

    cr_assert_eq(module.hasConfig("host"), true);
    cr_assert_eq(module.hasConfig("port"), true);
    cr_assert_eq(module.hasConfig(""), false);
    cr_assert_eq(module.hasConfig("issou"), false);
}

Test(ModuleConf, getConfig)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(std::make_unique<yconf::ConfigNode>(node), "/etc/zia/module.d");

    cr_assert_eq(module.getConfig("host"), "localhost");
    cr_assert_eq(module.getConfig("port"), "9000");
}

Test(ModuleConf, getConfigs)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(std::make_unique<yconf::ConfigNode>(node), "/etc/zia/module.d");

    std::unordered_map<std::string, std::string> map;
    map.emplace("host", "localhost");
    map.emplace("port", "9000");
    cr_assert_eq(module.getConfigs(), map);
}

Test(ModuleConf, getConfigsName)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(std::make_unique<yconf::ConfigNode>(node), "/etc/zia/module.d");

    std::vector<std::string> names;
    names.push_back("host");
    names.push_back("port");
    cr_assert_eq(module.getConfigsName(), names);
}
