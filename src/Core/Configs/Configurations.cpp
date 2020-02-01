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

#include <iostream>
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
    std::string modulesPath;
    std::vector<core::config::Host> hosts;
    std::unique_ptr<IConfigNode> yml = std::make_unique<yconf::ConfigNode>(this->m_filename);
    modulesPath = yml->getValue("modulespath");
    auto hostsArrat = yml->getNodeArray("hosts");
    if (hostsArrat.size() == 0)
        throw std::runtime_error("There should be at least one host");
    for (const auto &host : hostsArrat)
        hosts.push_back(*host);
    this->m_hosts = hosts;
    this->m_modulesPath = modulesPath;
}

void core::Configurations::print() const
{
    std::cout << "modulespath: " << this->m_modulesPath << std::endl;
    std::cout << "hosts:" << std::endl;
    for (const auto &host : this->m_hosts) {
        std::cout << "  - domain: " << host.getDomain() << std::endl;
        std::cout << "    listen:" << std::endl;
        std::cout << "      port: " << host.getPort() << std::endl;
        auto modules = host.getModules();
        if (modules.size() > 0) {
            std::cout << "      modules:" << std::endl;
            for (const auto &module : modules) {
                std::cout << "        - name: " << module.first << std::endl;
                auto configs = module.second.getConfigs();
                if (configs.size() > 0) {
                    std::cout << "          configs:" << std::endl;
                    for (const auto &config : configs)
                        std::cout << "            " << config.first << ": " << config.second << std::endl;
                }
            }
        }
        auto routes = host.getRoutes();
        if (routes.size() > 0) {
            std::cout << "      routes:" << std::endl;
            for (const auto &route : routes) {
                std::cout << "        - name: " << route.getName() << std::endl;
                auto modules = route.getModules();
                if (modules.size() > 0) {
                    std::cout << "          modules:" << std::endl;
                    for (const auto &module : modules) {
                        std::cout << "            - name: " << module.first << std::endl;
                        auto configs = module.second.getConfigs();
                        if (configs.size() > 0) {
                            std::cout << "              configs:" << std::endl;
                            for (const auto &config : configs)
                                std::cout << "                " << config.first << ": " << config.second << std::endl;
                        }
                    }
                }
            }
        }
    }
}
