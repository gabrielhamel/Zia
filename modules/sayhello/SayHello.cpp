/**
 * @file sayHello.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief An basic module who say hello at each requests
 * @version 1.0
 * @date 2020-02-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <boost/dll/alias.hpp>
#include <iostream>

#include "SayHello.hpp"

module::SayHello::SayHello()
{

}

module::SayHello::~SayHello()
{

}

std::string module::SayHello::name() const noexcept
{
    return std::move(std::string("SayHello"));
}

bool module::SayHello::newConnection(const net::IClient &client) noexcept
{
    std::cout << "newConnection()" << std::endl;
    return true;
}

bool module::SayHello::disconnection(const net::IClient &client) noexcept
{
    std::cout << "disconnection()" << std::endl;
    return true;
}

bool module::SayHello::setConfigurations(Configs configs) noexcept
{
    std::cout << "setConfigurations()" << std::endl;
    return true;
}

bool module::SayHello::afterReceive(const net::IClient &client, std::string &buffer) noexcept
{
    std::cout << "afterReceive()" << std::endl;
    return true;
}

bool module::SayHello::afterUnpacked(const net::IClient &client, http::IRequest &request) noexcept
{
    std::cout << "afterUnpacked()" << std::endl;
    return true;
}

bool module::SayHello::execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept
{
    std::cout << "execute()" << std::endl;
    return true;
}

bool module::SayHello::beforePacked(const net::IClient &client, http::IResponse &response) noexcept
{
    std::cout << "beforePacked()" << std::endl;
    return true;
}

bool module::SayHello::beforeSend(const net::IClient &client, std::string &buffer) noexcept
{
    std::cout << "beforeSend()" << std::endl;
    return true;
}

module::Api *factory()
{
    return new module::SayHello();
}

BOOST_DLL_ALIAS(factory, create_module)
