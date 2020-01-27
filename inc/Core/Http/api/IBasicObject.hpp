#ifndef IBASIC_OBJECT_HPP
#define IBASIC_OBJECT_HPP

#include <string>
#include <vector>

namespace http
{

/**
 * @brief http::IBasicObject is a interface that describe same object in a http request / response
 *
 */
struct IBasicObject
{

    /**
     * @brief Default destructor
     *
     */
    virtual ~IBasicObject() = default;

    /**
     * @brief Return the protocol of the object
     *
     */
    virtual std::string protocol() const noexcept = 0;

    /**
     * @brief Checks if in object, there are a named 'key' header parameter
     *
     * In http object there are some header parameters like "Content-Lenght: 166", "host: localhost".
     * They are described by "{KEY}: {VALUE}"
     */
    virtual bool headerParameterExist(const std::string &key) const noexcept = 0;

    /**
     * @brief Return the header parameter "key" found in the object
     *
     * In http object there are some header parameters like "Content-Lenght: 166", "host: localhost".
     * They are described by "{KEY}: {VALUE}"
     * Return an empty string if the parameters key not exist
     */
    virtual std::string headerParameter(const std::string &key) const noexcept = 0;

    /**
     * @brief Add / Update a header parameter
     *
     * In http object there are some header parameters like "Content-Lenght: 166", "host: localhost".
     * They are described by "{KEY}: {VALUE}"
     * Return false if the key or value aren't valid
     */
    virtual bool headerParameter(std::string key, std::string value) noexcept = 0;

    /**
     * @brief Return the body of the object
     *
     * Sometimes in object like POST there are a body
     * He can take any form (json, form-url-encoded, xml, plain text, ...)
     */
    virtual std::string body() const noexcept = 0;

    /**
     * @brief Set / Add a new body in the object
     *
     * Sometimes in object like POST there are a body
     * He can take any form (json, form-url-encoded, xml, plain text, ...)
     * Change / Add the 'Content-Length' header parameter
     * Return false if the body is empty or too large...
     */
    virtual bool body(std::string body) noexcept = 0;

    /**
     * @brief Append data in the body or create it if not exist
     *
     * Sometimes in object like POST there are a body
     * He can take any form (json, form-url-encoded, xml, plain text, ...)
     * Change / Add the 'Content-Length' header parameter
     * Return false if the body is empty or too large...
     */
    virtual bool bodyAppend(std::string body) noexcept = 0;

    /**
     * @brief Transform this object in a true http object
     *
     */
    virtual std::string serialize() const noexcept = 0;

};

} // namespace http

#endif // IBASIC_OBJECT_HPP
