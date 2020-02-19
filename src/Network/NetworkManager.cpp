/**
 * @file NetworkManager.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-02-11
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "NetworkManager.hpp"
#include "Configurations.hpp"

net::NetworkManager::NetworkManager(const core::config::Host &configs) :
m_configs(configs)
{
    const auto modules = configs.getModules();
    for (const auto &module : modules) {
        auto tmp = std::pair<std::string, std::unique_ptr<Module>>(module.first, std::move(instanciateModule(module.first)));
        this->m_modulesListen.push_back(std::move(tmp));
        this->m_modulesListen.back().second->get().setConfigurations(module.second.getConfigs());
    }
    for (const auto &route : configs.getRoutes())
        for (const auto &module : route.getModules()) {
            auto tmp = std::pair<std::regex, std::unique_ptr<Module>>(route.getPattern(), std::move(instanciateModule(module.first)));
            this->m_modulesRoutes.push_back(std::move(tmp));
            this->m_modulesRoutes.back().second->get().setConfigurations(module.second.getConfigs());
        }
}

std::unique_ptr<Module> net::NetworkManager::instanciateModule(const std::string &name) const
{
    for (auto file : core::Configurations::getAllDynName()) {
        auto ptr = std::make_unique<Module>(file);
        if (ptr->get().name() == name)
            return std::move(ptr);
    }
    throw std::runtime_error("Module " + name + " doesn't exists");
}

net::NetworkManager::~NetworkManager()
{

}

void net::NetworkManager::newClient(boost::shared_ptr<net::IClient> client)
{
    for (const auto &module : this->m_modulesListen)
        module.second->get().newConnection(*client);
    for (const auto &module : this->m_modulesRoutes)
        module.second->get().newConnection(*client);
}

void net::NetworkManager::removeClient(boost::shared_ptr<IClient> client)
{
    for (const auto &module : this->m_modulesListen)
        module.second->get().disconnection(*client);
    for (const auto &module : this->m_modulesRoutes)
        module.second->get().disconnection(*client);
}

void net::NetworkManager::sendBadRequest(net::IClient &client, std::string msg) const
{
    std::unique_ptr<http::IResponse> response(new HttpResponse());
    response->statusCode(400);
    response->statusMessage("Bad Request");
    response->body( "<html>\r\n"                                            \
                    "<head><title>400 Bad Request</title></head>\r\n"       \
                    "<body>\r\n"                                            \
                    "<center><h1>" + msg + "</h1></center>\r\n"             \
                    "<hr><center>zia/1.0.0 (Gab is a monster)</center>\r\n" \
                    "</body>\r\n"                                           \
                    "</html>\r\n");
    client.send(response->serialize());
}

void net::NetworkManager::recvData(boost::shared_ptr<net::IClient> client, std::string &data)
{
    try {
        for (const auto &module : this->m_modulesListen)
            module.second->get().afterReceive(*client, data);
        std::unique_ptr<http::IRequest> request(new HttpRequest(data));
        for (const auto &module : this->m_modulesListen)
            module.second->get().afterUnpacked(*client, *request);
        std::unique_ptr<http::IResponse> response(new HttpResponse());
        for (const auto &module : this->m_modulesListen)
            module.second->get().execute(*client, *request, *response);
        for (const auto &module : this->m_modulesListen)
            module.second->get().beforePacked(*client, *response);
        std::string toSend(response->serialize());
        for (const auto &module : this->m_modulesListen)
            module.second->get().beforeSend(*client, toSend);
        client->send(toSend);
    }
    catch (const std::exception &e) {
        this->sendBadRequest(*client, e.what());
    }
    // TODO code retour + essai a l'infini tant que ça marche pas
}
