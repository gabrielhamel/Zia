/**
 * @file Configurations.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-23
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CONFIGURATIONS_HPP
#define CONFIGURATIONS_HPP

#include <string>
#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "Host.hpp"

namespace core {

class Configurations
{

private:

    std::string m_filename;

    std::string m_modulesPath;

    std::vector<core::config::Host> m_hosts;

public:

    Configurations(const std::string &filename);

    ~Configurations();

    void updatePath(const std::string &filename);

    void reload();

    void print() const;

};

} // namespace core

#endif // CONFIGURATIONS_HPP
