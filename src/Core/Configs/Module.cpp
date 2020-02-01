/**
 * @file Module.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-25
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <exception>

#include "Module.hpp"

core::config::Module::Module(const IConfigNode &node)
{
    this->m_name = node.getValue("name");
    try {
        this->m_configs = node.getAllScalarsOf("configs");
    }
    catch (const std::runtime_error &e) {
        if (std::string(e.what()) == "Non scalar value in node")
            throw e;
    }
    catch (...) {

    }
}

core::config::Module::~Module()
{

}

std::string core::config::Module::getConfig(const std::string &key) const
{
    return this->m_configs.at(key);
}

const std::unordered_map<std::string, std::string> &core::config::Module::getConfigs() const
{
    return this->m_configs;
}

std::string core::config::Module::getName() const
{
    return this->m_name;
}

std::vector<std::string> core::config::Module::getConfigsName() const
{
    std::vector<std::string> res;
    for (auto &module : this->m_configs)
        res.push_back(module.first);
    return res;
}

bool core::config::Module::hasConfig(const std::string &key) const
{
    return this->m_configs.find(key) != this->m_configs.end();
}
