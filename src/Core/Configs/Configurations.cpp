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
#include <mutex>

#include "Configurations.hpp"

#include <boost/dll.hpp>
#include <boost/foreach.hpp>

using namespace boost::filesystem;

std::string core::Configurations::modulesPath("");

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
    std::string modulesPath2;
    std::vector<core::config::Host> hosts;
    std::unique_ptr<IConfigNode> yml = std::make_unique<yconf::ConfigNode>(this->m_filename);
    modulesPath2 = yml->getValue("modulespath");
    auto hostsArrat = yml->getNodeArray("hosts");
    if (hostsArrat.size() == 0)
        throw std::runtime_error("There should be at least one host");
    for (const auto &host : hostsArrat)
        hosts.push_back(*host);
    this->m_hosts = hosts;
    core::Configurations::modulesPath = modulesPath2;
}

void core::Configurations::print() const
{
    std::cout << "modulespath: " << core::Configurations::modulesPath << std::endl;
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

const core::config::Host &core::Configurations::getHostByDomain(const std::string &domain) const
{
    for (const auto &host : this->m_hosts)
        if (host.getDomain() == domain)
            return host;
    throw std::runtime_error("Cannot find that host");
}

const core::config::Host &core::Configurations::getHostByPort(unsigned short port) const
{
    auto res = std::find_if(std::begin(this->m_hosts), std::end(this->m_hosts), [port](const core::config::Host &host) {
        return host.getPort() == port;
    });
    return *res;
}

const std::vector<core::config::Host> &core::Configurations::getHosts() const
{
    return this->m_hosts;
}

std::vector<std::string> core::Configurations::getAllDynName()
{
    std::regex check("^.{1,}\\.(dll|so)$");
    std::vector<std::string> res;
    path targetDir(Configurations::modulesPath);
    directory_iterator iter(targetDir), eod;
    BOOST_FOREACH(path const &i, std::make_pair(iter, eod)) {
        if (!std::regex_search(i.string(), check))
            continue;
        if (is_regular_file(i)) {
            boost::dll::shared_library lib(i.string());
            if (!lib.has("create_module"))
                continue;
            res.push_back(i.string());
        }
    }
    return res;
}
