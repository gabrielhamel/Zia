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
#include <boost/filesystem.hpp>

#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "Host.hpp"

namespace core {

class Configurations
{

private:

    std::string m_filename;

    std::vector<core::config::Host> m_hosts;

public:

    Configurations(const std::string &filename);

    ~Configurations();

    void updatePath(const std::string &filename);

    void reload();

    void print() const;

    const core::config::Host &getHostByDomain(const std::string &domain) const;

    const core::config::Host &getHostByPort(unsigned short port) const;

    const std::vector<core::config::Host> &getHosts() const;

    static std::vector<std::string> getAllDynName();

    static std::string modulesPath;

};

} // namespace core

#endif // CONFIGURATIONS_HPP
