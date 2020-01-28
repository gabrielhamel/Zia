/**
 * @file Route.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-28
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CONFROUTE_HPP
#define CONFROUTE_HPP

#include <regex>

#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include <Module.hpp>

namespace core::config
{

class Route
{

private:

    std::regex m_pattern;

    std::unordered_map<std::string, core::config::Module> m_modules;

public:

    /**
     * An node:
     * - name: ^/*.php$
     *    modules:
     *      - name: php-module
     *        configs:
     *          host: localhost
     *          port: 9000
     */
    Route(const std::unique_ptr<IConfigNode> node);

    ~Route();

    std::regex getPattern() const;

    std::vector<std::string> getModulesName() const;

    std::unordered_map<std::string, core::config::Module> getModules() const;

    core::config::Module getModule(const std::string &name) const;

    bool hasModule(const std::string &name) const;

};

} // namespace core::config

#endif // CONFROUTE_HPP
