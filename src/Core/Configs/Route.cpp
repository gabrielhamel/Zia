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

core::config::Route::Route(const IConfigNode &node)
{
    this->m_patternStr = node.getValue("name");
    this->m_pattern = this->m_patternStr;
    auto modules = node.getNodeArray("modules");
    for (const auto &module : modules)
        this->addModule(*module);
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
