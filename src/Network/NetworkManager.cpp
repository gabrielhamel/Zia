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

void net::NetworkManager::sendInternalError(net::IClient &client, std::string msg) const
{
    std::unique_ptr<http::IResponse> response(new HttpResponse());
    response->statusCode(500);
    response->statusMessage("Internal server error");
    response->body( "<html>\r\n"                                                \
                    "<head><title>500 Internal server error</title></head>\r\n" \
                    "<body>\r\n"                                                \
                    "<center><h1>" + msg + "</h1></center>\r\n"                 \
                    "<hr><center>zia/1.0.0 (Gab is a monster)</center>\r\n"     \
                    "</body>\r\n"                                               \
                    "</html>\r\n");
    client.send(response->serialize());
}


void net::NetworkManager::recvData(boost::shared_ptr<net::IClient> client, std::string &data)
{
    std::unique_ptr<http::IRequest> request;
    for (const auto &module : this->m_modulesListen)
        if (!module.second->get().afterReceive(*client, data)) {
            this->sendBadRequest(*client, "Module error (afterReceive): " + module.second->get().name());
            return;
        }
    try {
        request = std::make_unique<HttpRequest>(data);
    }
    catch (const std::exception &e) {
        this->sendBadRequest(*client, "Bad request: " + std::string(e.what()));
        return;
    }
    // Request modules
    for (const auto &module : this->m_modulesListen)
        if (!module.second->get().afterUnpacked(*client, *request)) {
            this->sendBadRequest(*client, "Module error (afterUnpacked): " + module.second->get().name());
            return;
        }
    for (const auto &module : this->m_modulesRoutes) {
        if (!std::regex_search(request->route(), module.first))
            continue;
        if (!module.second->get().afterUnpacked(*client, *request)) {
            this->sendBadRequest(*client, "Module error (afterUnpacked): " + module.second->get().name());
            return;
        }
        break;
    }
    std::unique_ptr<http::IResponse> response;
    try {
        response = std::make_unique<HttpResponse>();
    }
    catch (const std::exception &e) {
        this->sendInternalError(*client, "Cannot respond: " + std::string(e.what()));
        return;
    }
    for (const auto &module : this->m_modulesListen)
        if (!module.second->get().execute(*client, *request, *response)) {
            this->sendInternalError(*client, "Module error (execute): " + module.second->get().name());
            return;
        }
    for (const auto &module : this->m_modulesRoutes) {
        if (!std::regex_search(request->route(), module.first))
            continue;
        if (!module.second->get().execute(*client, *request, *response)) {
            this->sendInternalError(*client, "Module error (execute): " + module.second->get().name());
            return;
        }
        break;
    }
    for (const auto &module : this->m_modulesListen)
        if (!module.second->get().beforePacked(*client, *response)) {
            this->sendInternalError(*client, "Module error (beforePacked): " + module.second->get().name());
            return;
        }
    for (const auto &module : this->m_modulesRoutes) {
        if (!std::regex_search(request->route(), module.first))
            continue;
        if (!module.second->get().beforePacked(*client, *response)) {
            this->sendInternalError(*client, "Module error (beforePacked): " + module.second->get().name());
            return;
        }
        break;
    }
    std::string toSend;
    try {
        toSend = response->serialize();
    }
    catch (const std::exception &e) {
        this->sendInternalError(*client, "Cannot pack response: " + std::string(e.what()));
        return;
    }
    for (const auto &module : this->m_modulesListen)
        if (!module.second->get().beforeSend(*client, toSend)) {
            this->sendInternalError(*client, "Module error (beforeSend): " + module.second->get().name());
            return;
        }
    for (const auto &module : this->m_modulesRoutes) {
        if (!std::regex_search(request->route(), module.first))
            continue;
        if (!module.second->get().beforeSend(*client, toSend)) {
            this->sendInternalError(*client, "Module error (beforeSend): " + module.second->get().name());
            return;
        }
        break;
    }
    client->send(toSend);
}
