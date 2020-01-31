/**
 * @file Host.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-25
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CONFHOST_HPP
#define CONFHOST_HPP

#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "ModuleContainer.hpp"

namespace core::config
{

class Host : public ModuleContainer
{

private:

    const std::string m_defaultPath;

    std::string m_domain;

    std::uint16_t port;


public:

    Host(const IConfigNode &node);

    ~Host();

};

} // namespace core::config

#endif // CONFHOST_HPP
