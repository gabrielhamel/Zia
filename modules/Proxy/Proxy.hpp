/**
 * @file Proxy.hpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief
 * @version 1.0
 * @date 2020-02-25
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef PROXY_MODULE_HPP
#define PROXY_MODULE_HPP

#include "ModuleApi.hpp"

#include <boost/asio.hpp>

using namespace boost::asio;

namespace module
{

class Proxy : public Api
{

private:

    ip::address_v4 m_ip;

    uint16_t m_port;

public:

    Proxy();

    ~Proxy();

    std::string name() const noexcept;

    bool newConnection(const net::IClient &client) noexcept;

    bool disconnection(const net::IClient &client) noexcept;

    bool setConfigurations(Configs configs) noexcept;

    bool afterReceive(const net::IClient &client, std::string &buffer) noexcept;

    bool afterUnpacked(const net::IClient &client, http::IRequest &request) noexcept;

    bool execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept;

    bool beforePacked(const net::IClient &client, http::IResponse &response) noexcept;

    bool beforeSend(const net::IClient &client, std::string &buffer) noexcept;

};

} // namespace module

#endif // PROXY_MODULE_HPP
