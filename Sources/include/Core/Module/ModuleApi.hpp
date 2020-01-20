#ifndef IMODULE_API_HPP
#define IMODULE_API_HPP

#include "IResponse.hpp"
#include "IRequest.hpp"
#include "IClient.hpp"

namespace module
{

struct Api
{
    /**
     * @brief Default destructor
     *
     */
    virtual ~Api() = default;

    /**
     * @brief When a new client connects to the http server
     *
     * It can be useful to store the id of the client
     * to recognize him after
     */
    virtual bool newConnection(const net::IClient &client) noexcept = 0;

    /**
     * @brief Just before the deserialization of the packet
     *
     * It can be useful to decrypt an tls packet or compressed packet (gzip, ...)
     */
    virtual bool afterReceive(const net::IClient &client, std::string &buffer) noexcept = 0;

    /**
     * @brief This is the main behavior of the module
     *
     * Reaction to the client's request
     */
    virtual bool execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept = 0;

    /**
     * @brief Just before packet delivery
     *
     * Useful if we need to add something in the packet or to encrypt / compress it
     */
    virtual bool beforeSend(const net::IClient &client, std::string &buffer) noexcept = 0;

};

} // namespace mod

#endif // IMODULE_API_HPP
