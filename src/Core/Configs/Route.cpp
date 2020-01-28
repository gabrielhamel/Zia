/**
 * @file Route.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-28
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Route.hpp"

core::config::Route::Route(const std::unique_ptr<IConfigNode> node)
{
    this->m_pattern = node->getValue("name");
    auto modules = node->getChild("modules");
    // #TODO
}

core::config::Route::~Route()
{

}

std::regex core::config::Route::getPattern() const
{
    return this->m_pattern;
}

std::vector<std::string> core::config::Route::getModulesName() const
{
    std::vector<std::string> res;
    for (auto &module : this->m_modules)
        res.push_back(module.first);
    return res;
}

std::unordered_map<std::string, core::config::Module> core::config::Route::getModules() const
{
    return this->m_modules;
}

core::config::Module core::config::Route::getModule(const std::string &name) const
{
    return this->m_modules.at(name);
}

bool core::config::Route::hasModule(const std::string &name) const
{
    return this->m_modules.find(name) != this->m_modules.end();
}
