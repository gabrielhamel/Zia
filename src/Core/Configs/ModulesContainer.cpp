/**
 * @file ModulesContainer.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-31
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "ModulesContainer.hpp"

core::config::ModulesContainer::ModulesContainer()
{

}

core::config::ModulesContainer::~ModulesContainer()
{

}

std::vector<std::string> core::config::ModulesContainer::getModulesName() const
{
    std::vector<std::string> res;
    for (auto &module : this->m_modules)
        res.push_back(module.first);
    return res;
}

const std::unordered_map<std::string, core::config::Module> &core::config::ModulesContainer::getModules() const
{
    return this->m_modules;
}

core::config::Module core::config::ModulesContainer::getModule(const std::string &name) const
{
    return this->m_modules.at(name);
}

bool core::config::ModulesContainer::hasModule(const std::string &name) const
{
    return this->m_modules.find(name) != this->m_modules.end();
}

void core::config::ModulesContainer::addModule(const IConfigNode &config)
{
    this->m_modules.emplace(config.getValue("name"), core::config::Module(config));
}
