/**
 * @file sayHello.hpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @brief An basic module who say hello at each requests
 * @version 1.0
 * @date 2020-02-17
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef MODULE_SAY_HELLO_HPP
#define MODULE_SAY_HELLO_HPP

#include "ModuleApi.hpp"

namespace module
{

class SayHello : public Api
{

public:

    SayHello();

    ~SayHello();

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

#endif // MODULE_SAY_HELLO_HPP
