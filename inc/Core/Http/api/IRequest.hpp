#ifndef IREQUEST_HPP
#define IREQUEST_HPP

#include "IBasicObject.hpp"

namespace http
{

/**
 * @brief http::Verb describe all possible actions in a http request
 *
 */
enum Verb
{
    HTTP_GET,
    HTTP_HEAD,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE,
    HTTP_CONNECT,
    HTTP_OPTIONS,
    HTTP_TRACE,
    HTTP_PATCH
};

/**
 * @brief http::IRequest is a interface that encapsulates a http request
 *
 */
struct IRequest : public http::IBasicObject
{

    /**
     * @brief Default destructor
     *
     */
    virtual ~IRequest() = default;

    /**
     * @brief Returns the http verb
     *
     * The verb can be GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE, PATCH
     */
    virtual http::Verb verb() const noexcept = 0;

    /**
     * @brief Change the verb of the request
     *
     * The verb can be GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE, PATCH
     * Return true if there are no problems
     */
    virtual bool verb(http::Verb verb) noexcept = 0;

    /**
     * @brief Returns the route
     *
     * In "http://example.com/index?key=value&test=yes" returns "/index"
     * She doesn't returns the query parameters ("?key=value&test=yes")
     */
    virtual std::string route() const noexcept = 0;

    /**
     * @brief Change the route
     *
     * In "http://example.com/index?key=value&test=yes" returns "/index"
     * She doesn't returns the query parameters ("?key=value&test=yes")
     * Return false if route aren't valid
     */
    virtual bool route(std::string route) noexcept = 0;

    /**
     * @brief Checks if in the route, there are a named 'key' query parameter
     *
     * In "http://example.com/index?key=value&test=yes" the query parameters
     * are "key" and "test" for the values of "value" and "yes"
     */
    virtual bool queryParameterExist(const std::string &key) const noexcept = 0;

    /**
     * @brief Return the query parameter "key" found in the route
     *
     * In "http://example.com/index?key=value&test=yes" the query parameters
     * are "key" and "test" for the values of "value" and "yes"
     * Return a empty string if the parameter is not found
     */
    virtual std::string queryParameter(const std::string &key) const noexcept = 0;

    /**
     * @brief Add / Update a query parameter
     *
     * In "http://example.com/index?key=value&test=yes" the query parameters
     * are "key" and "test" for the values of "value" and "yes"
     * Return false if the parameter is not valid
     */
    virtual bool queryParameter(std::string key, std::string value) noexcept = 0;

    /**
     * @brief Return the value of the cookie 'name'
     * In header there are an header parameter name 'Cookie' who has
     * all cookies of the request
     * ex: "Cookie: yummy_cookie=choco; tasty_cookie=strawberry"
     * Return a empty string if the cookie not exist
     */
    virtual std::string cookie(const std::string &name) const noexcept = 0;

};

} // namespace http

#endif // IREQUEST_HPP
