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
#include <iostream>
#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "Modules.hpp"

const static std::string example =
    "name: php-module\n"
    "configs:\n"
    "  host: localhost\n"
    "  port: 9000\n";

Test(ModuleConf, name)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(yconf::ConfigNode(node));

    cr_assert_eq(module.getName(), "php-module");
}

Test(ModuleConf, hasConfig)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(yconf::ConfigNode(node));

    cr_assert_eq(module.hasConfig("host"), true);
    cr_assert_eq(module.hasConfig("port"), true);
    cr_assert_eq(module.hasConfig(""), false);
    cr_assert_eq(module.hasConfig("issou"), false);
}

Test(ModuleConf, getConfig)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(yconf::ConfigNode(node));

    cr_assert_eq(module.getConfig("host"), "localhost");
    cr_assert_eq(module.getConfig("port"), "9000");
}

Test(ModuleConf, getConfigs)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(yconf::ConfigNode(node));

    std::unordered_map<std::string, std::string> map;
    map.emplace("host", "localhost");
    map.emplace("port", "9000");
    cr_assert_eq(module.getConfigs(), map);
}

Test(ModuleConf, getConfigsName)
{
    auto node = YAML::Load(example);
    auto module = core::config::Module(yconf::ConfigNode(node));

    auto res = module.getConfigsName();
    cr_assert_neq(std::find(res.begin(), res.end(), "port"), res.end());
    cr_assert_neq(std::find(res.begin(), res.end(), "host"), res.end());
}

Test(ModuleConf, withoutConfig)
{
    const std::string newExample = "name: php-module";
    auto node = YAML::Load(newExample);
    auto module = core::config::Module(yconf::ConfigNode(node));
    std::vector<std::string> names;
    cr_assert_eq(module.getConfigsName(), names);
    cr_assert_eq(module.getName(), "php-module");
}
