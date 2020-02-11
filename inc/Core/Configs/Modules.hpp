/**
 * @file Modules.hpp
 * @author Gabriel Hamel (gabriel.hamel.pro@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-02-11
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CONF_MODULE_HPP
#define CONF_MODULE_HPP

#include <string>
#include <unordered_map>

#include "IConfigNode.hpp"

namespace core::config {

class Module
{

private:

    std::string m_name;

    std::unordered_map<std::string, std::string> m_configs;

public:

    Module(const IConfigNode &node);

    ~Module();

    std::string getConfig(const std::string &key) const;

    const std::unordered_map<std::string, std::string> &getConfigs() const;

    std::string getName() const;

    std::vector<std::string> getConfigsName() const;

    bool hasConfig(const std::string &key) const;

};

} // namespace core::config

#endif // CONF_MODULE_HPP
