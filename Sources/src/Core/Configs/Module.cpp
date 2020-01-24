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

#include "Module.hpp"

core::config::Module::Module(const std::unique_ptr<IConfigNode> node, const std::string &defaultModulePath) :
m_defaultPath(defaultModulePath)
{
    this->m_name = node->getValue("name");
    this->m_configs = node->getChild("configs");
}

core::config::Module::~Module()
{

}

std::string core::config::Module::getConfig(const std::string &key) const
{
    return this->m_configs->getValue(key);
}

std::string core::config::Module::getDefaultPath() const
{
    return this->m_defaultPath;
}

std::string core::config::Module::getName() const
{
    return this->m_name;
}
