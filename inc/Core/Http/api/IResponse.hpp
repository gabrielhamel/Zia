#ifndef IRESPONSE_HPP
#define IRESPONSE_HPP

#include "IBasicObject.hpp"

typedef std::vector<std::pair<std::string, std::string>> CookieOptions;

namespace http
{

/**
 * @brief http::IResponse is a interface that encapsulates a http response
 *
 */
struct IResponse : public http::IBasicObject
{

    /**
     * @brief Default destructor
     *
     */
    virtual ~IResponse() = default;

    /**
     * @brief Returns the status code of the response
     *
     * In http response there are always status code like 200 or 404
     * To describe if the request is executed correctly
     */
    virtual int statusCode() const noexcept = 0;

    /**
     * @brief Set the status code of the response
     *
     * In http response there are always status code like "200" or "404"
     * To describe if the request is executed correctly
     * Return false if the status code isn't valid
     */
    virtual bool statusCode(int statusCode) noexcept = 0;

    /**
     * @brief Returns the status message of the response
     *
     * In http response there are always status message
     * after the status code like "200 OK" or "404 Not found"
     */
    virtual std::string statusMessage() const noexcept = 0;

    /**
     * @brief Set the status message of the response
     *
     * In http response there are always status message
     * after the status code like "200 OK" or "404 Not found"
     * Return false if the status message isn't valid
     */
    virtual bool statusMessage(std::string statusMessage) noexcept = 0;

    /**
     * @brief Return the value of the cookie 'name'
     * In header there are an header parameter name 'Cookie' who has
     * all cookies of the request
     * ex: "Cookie: yummy_cookie=choco; tasty_cookie=strawberry"
     * He can have options like Expires, Domain, Max-Age, ...
     * Return false if the name or the value are invalids
     */
    virtual bool setCookie(std::string name, std::string value, CookieOptions options = CookieOptions()) noexcept = 0;

};

} // namespace http

#endif // IRESPONSE_HPP
