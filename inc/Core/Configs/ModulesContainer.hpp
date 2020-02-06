/**
 * @file ModulesContainer.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-31
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CONFMODULESCONTAINER_HPP
#define CONFMODULESCONTAINER_HPP

#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"
#include "Modules.hpp"

namespace core::config
{

class ModulesContainer
{

private:

    std::unordered_map<std::string, core::config::Module> m_modules;

public:

    ModulesContainer();

    ~ModulesContainer();

    std::vector<std::string> getModulesName() const;

    const std::unordered_map<std::string, core::config::Module> &getModules() const;

    core::config::Module getModule(const std::string &name) const;

    bool hasModule(const std::string &name) const;

protected:

    void addModule(const IConfigNode &config);

};

} // namespace core::config

#endif // CONFMODULESCONTAINER_HPP
