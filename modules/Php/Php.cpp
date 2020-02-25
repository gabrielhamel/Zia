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
#include <sstream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <regex>
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
    const auto &root = configs.find("root");
    if (root == configs.end()) {
        std::cerr << "Missing root folder" << std::endl;
        return false;
    }
    m_rootFolder = root->second;
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

bool module::Php::responseError(int status, std::string message, http::IResponse &response) const
{
    response.statusCode(status);
    response.statusMessage(message);
    response.body( "<html>\r\n"                                            \
                    "<head><title>" + std::string(std::to_string(status) + std::string(" ") + message) + "</title></head>\r\n"       \
                    "<body>\r\n"                                            \
                    "<center><h1>" + std::string(std::to_string(status) + std::string(" ") + message) + "</h1></center>\r\n"             \
                    "<hr><center>zia/1.0.0 (Gab is a monster)</center>\r\n" \
                    "</body>\r\n"                                           \
                    "</html>\r\n");
    return true;
}

bool module::Php::execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept
{
    auto path = this->m_rootFolder + "/" + request.route();
    boost::filesystem::path file(path);
    if (!boost::filesystem::exists(file) || !boost::filesystem::is_regular_file(file))
        return responseError(404, "Not found", response);
    try {
        // Use path variable
        std::cout << "LOAD PHP " << path << std::endl;
    }
    catch (const std::exception &e) {
        return false;
    }
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
