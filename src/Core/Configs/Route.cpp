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

#include <iostream>
#include "Route.hpp"

core::config::Route::Route(const IConfigNode &node, const std::string &defaultModulePath) :
m_defaultModulePath(defaultModulePath)
{
    this->m_patternStr = node.getValue("name");
    this->m_pattern = this->m_patternStr;
    std::vector<std::string> modules;

    // TODO try catch
    modules = node.getArray("modules");
    std::cout << "--- start ---" << std::endl;
    for (const std::string &module : modules)
        std::cout << module << std::endl;
    std::cout << "---- end ----" << std::endl;
    // TODO
}

core::config::Route::~Route()
{

}

std::regex core::config::Route::getPattern() const
{
    return this->m_pattern;
}

std::string core::config::Route::getName() const
{
    return this->m_patternStr;
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
