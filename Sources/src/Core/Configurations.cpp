/**
 * @file Configurations.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-23
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Configurations.hpp"

core::Configurations::Configurations(const std::string &filename)
{
    this->updatePath(filename);
}

core::Configurations::~Configurations()
{

}

void core::Configurations::updatePath(const std::string &filename)
{
    this->m_filename = filename;
    this->reload();
}

void core::Configurations::reload()
{
    // Load configs
}
