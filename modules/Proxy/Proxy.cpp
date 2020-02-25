/**
 * @file Proxy.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2020-02-25
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <boost/dll.hpp>
#include <iostream>
#include <sstream>

#include "HttpResponse.hpp"
#include "Proxy.hpp"

using namespace boost::asio;

module::Proxy::Proxy()
{

}

module::Proxy::~Proxy()
{

}

std::string module::Proxy::name() const noexcept
{
    return std::move(std::string("proxy"));
}

bool module::Proxy::newConnection(const net::IClient &client) noexcept
{
    return true;
}

bool module::Proxy::disconnection(const net::IClient &client) noexcept
{
    return true;
}

bool module::Proxy::setConfigurations(Configs configs) noexcept
{
    const auto &hostname = configs.find("hostname");
    if (hostname == configs.end()) {
        std::cerr << "Missing hostname" << std::endl;
        return false;
    }
    this->m_ip = ip::make_address_v4(hostname->second);
    const auto &port = configs.find("port");
    if (port == configs.end()) {
        std::cerr << "Missing port" << std::endl;
        return false;
    }
    this->m_port = std::stoi(port->second);
    return true;
}

bool module::Proxy::afterReceive(const net::IClient &client, std::string &buffer) noexcept
{
    return true;
}

bool module::Proxy::afterUnpacked(const net::IClient &client, http::IRequest &request) noexcept
{
    return true;
}

bool module::Proxy::execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept
{
    try {
        ip::tcp::endpoint endpoint(this->m_ip, this->m_port);
        io_context context;
        ip::tcp::socket socket(context);
        socket.connect(endpoint);
        request.headerParameter("Connection", "close");
        socket.send(buffer(request.serialize()));
        streambuf responseBuff;
        boost::system::error_code error;
        std::stringstream message;
        while (read(socket, responseBuff, transfer_at_least(1), error))
            message << &responseBuff;
        std::cout << "LOL\n" << message.str() << std::endl;
        auto dest = new HttpResponse(message.str());
        response.statusCode(dest->statusCode());
        response.statusMessage(dest->statusMessage());
        response.body(dest->body());
        delete dest;
        response.headerParameter("Connection", "keep-alive");
        std::cout << "LOL2\n" << response.serialize() << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool module::Proxy::beforePacked(const net::IClient &client, http::IResponse &response) noexcept
{
    return true;
}

bool module::Proxy::beforeSend(const net::IClient &client, std::string &buffer) noexcept
{
    return true;
}

module::Api *factory()
{
    return new module::Proxy();
}

BOOST_DLL_ALIAS(factory, create_module)
