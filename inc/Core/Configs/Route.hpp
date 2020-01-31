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
#include "ModulesContainer.hpp"

namespace core::config
{

class Route : public ModulesContainer
{

private:

    std::string m_patternStr;

    std::regex m_pattern;

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
    Route(const IConfigNode &node);

    ~Route();

    std::regex getPattern() const;

    std::string getName() const;

};

} // namespace core::config

#endif // CONFROUTE_HPP
