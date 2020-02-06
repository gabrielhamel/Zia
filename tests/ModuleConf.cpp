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

    std::vector<std::string> names;
    names.push_back("port");
    names.push_back("host");
    cr_assert_eq(module.getConfigsName(), names);
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

Test(ModuleConf, configAdvancedError)
{
    const std::string newExample =
    "name: php-module\n"
    "configs:\n"
    "  key:\n"
    "    key1: value1\n"
    "    key2: value2\n"
    "  port: 9000\n";
    auto node = YAML::Load(newExample);
    bool ok = false;
    try {
        auto module = core::config::Module(yconf::ConfigNode(node));
        module.getConfigsName();
    }
    catch (const std::exception &e) {
        if (std::string(e.what()) == "Non scalar value in node")
            ok = true;
    }
    cr_assert_eq(ok, true);
}
