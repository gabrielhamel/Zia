/**
 * @file Module.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-25
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CONFMODULE_HPP
#define CONFMODULE_HPP

#include <map>

#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"

namespace core::config
{

class Module
{

private:

    const std::string m_defaultPath;

    std::string m_name;

    std::unique_ptr<IConfigNode> m_configs;

public:

    /**
     * An node:
     * - name: php-module
     *   configs:
     *     host: localhost
     *     port: 9000
     */
    Module(const std::unique_ptr<IConfigNode> node, const std::string &defaultModulePath);

    ~Module();

    std::string getConfig(const std::string &key) const;

    std::string getDefaultPath() const;

    std::string getName() const;

};

} // namespace core::config

#endif // CONFMODULE_HPP
