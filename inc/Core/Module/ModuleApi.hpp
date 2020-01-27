#ifndef IMODULE_API_HPP
#define IMODULE_API_HPP

#include <unordered_map>
#include "IResponse.hpp"
#include "IRequest.hpp"
#include "IClient.hpp"

typedef std::unordered_map<std::string, std::string> Configs;

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
     * @brief Returns the module name
     *
     */
    virtual std::string name() const noexcept = 0;

    /**
     * @brief When a new client connects to the http server
     *
     * It can be useful to store the id of the client
     * to recognize him after
     */
    virtual bool newConnection(const net::IClient &client) noexcept = 0;

    /**
     * @brief When a client disconnects
     *
     * To inform the module of the client's disconnection
     */
    virtual bool disconnection(const net::IClient &client) noexcept = 0;

    /**
     * @brief Set the Global configs of the module
     *
     */
    virtual bool setConfigurations(Configs configs) noexcept = 0;

    /**
     * @brief Just before the deserialization of the packet
     *
     * It can be useful to decrypt an tls packet
     */
    virtual bool afterReceive(const net::IClient &client, std::string &buffer) noexcept = 0;

    /**
     * @brief Call before the main behavior of the module
     *
     * It can be useful to decompresses a http body (gzip, ...)
     */
    virtual bool afterUnpacked(const net::IClient &client, http::IRequest &request) noexcept = 0;

    /**
     * @brief This is the main behavior of the module
     *
     * Reaction to the client's request
     */
    virtual bool execute(const net::IClient &client, http::IRequest &request, http::IResponse &response) noexcept = 0;

    /**
     * @brief Just before the serialization of the response
     *
     * Useful if we need to add something in the packet or to compress it
     */
    virtual bool beforePacked(const net::IClient &client, http::IResponse &response) noexcept = 0;

    /**
     * @brief Just before packet delivery
     *
     * Useful if we need to add something in the packet or to encrypt
     */
    virtual bool beforeSend(const net::IClient &client, std::string &buffer) noexcept = 0;

};

} // namespace module

#endif // IMODULE_API_HPP
