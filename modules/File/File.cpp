/**
 * @file File.cpp
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

#include "File.hpp"

module::File::File()
{

}

module::File::~File()
{

}

std::string module::File::name() const noexcept
{
    return std::move(std::string("file"));
}

bool module::File::newConnection(const net::IClient &client) noexcept
{
    return true;
}

bool module::File::disconnection(const net::IClient &client) noexcept
{
    return true;
}

bool module::File::setConfigurations(Configs configs) noexcept
{
    return true;
}

bool module::File::afterReceive(const net::IClient &client, std::string &buffer) noexcept
{
    return true;
}

bool module::File::afterUnpacked(const net::IClient &client, http::IRequest &request) noexcept
{
    return true;
}

bool module::File::execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept
{
    std::cout << "Into file" << std::endl;
    return true;
}

bool module::File::beforePacked(const net::IClient &client, http::IResponse &response) noexcept
{
    return true;
}

bool module::File::beforeSend(const net::IClient &client, std::string &buffer) noexcept
{
    return true;
}

module::Api *factory()
{
    return new module::File();
}

BOOST_DLL_ALIAS(factory, create_module)
