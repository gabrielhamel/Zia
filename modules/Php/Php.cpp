/**
 * @file Php.cpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2020-02-20
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <boost/dll/alias.hpp>
#include <iostream>

#include "Php.hpp"

module::Php::Php()
{

}

module::Php::~Php()
{

}

std::string module::Php::name() const noexcept
{
    return std::move(std::string("php"));
}

bool module::Php::newConnection(const net::IClient &client) noexcept
{
    return true;
}

bool module::Php::disconnection(const net::IClient &client) noexcept
{
    return true;
}

bool module::Php::setConfigurations(Configs configs) noexcept
{
    return true;
}

bool module::Php::afterReceive(const net::IClient &client, std::string &buffer) noexcept
{
    return true;
}

bool module::Php::afterUnpacked(const net::IClient &client, http::IRequest &request) noexcept
{
    return true;
}

bool module::Php::execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept
{
    std::cout << "Into php" << std::endl;
    return true;
}

bool module::Php::beforePacked(const net::IClient &client, http::IResponse &response) noexcept
{
    return true;
}

bool module::Php::beforeSend(const net::IClient &client, std::string &buffer) noexcept
{
    return true;
}

module::Api *factory()
{
    return new module::Php();
}

BOOST_DLL_ALIAS(factory, create_module)
