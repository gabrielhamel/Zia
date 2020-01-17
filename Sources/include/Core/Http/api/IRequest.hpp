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
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH
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
     * @brief Returns the verb
     *
     * The verb can be GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE, PATCH
     *
     * @return http::Verb
     */
    virtual http::Verb verb() const noexcept = 0;

    /**
     * @brief Change the verb of the request
     *
     * The verb can be GET, HEAD, POST, PUT, DELETE, CONNECT, OPTIONS, TRACE, PATCH
     *
     * @param verb
     */
    virtual void verb(http::Verb verb) = 0;

    /**
     * @brief Returns the route
     *
     * In "http://example.com/index?key=value&test=yes" returns "/index"
     * She doesn't returns the query parameters ("?key=value&test=yes")
     *
     * @return std::string
     */
    virtual std::string route() const noexcept = 0;

    /**
     * @brief Change the route
     *
     * In "http://example.com/index?key=value&test=yes" returns "/index"
     * She doesn't returns the query parameters ("?key=value&test=yes")
     * Throws a http::RouteException if route aren't valid
     *
     * @param route
     */
    virtual void route(std::string route) = 0;

    /**
     * @brief Checks if in the route, there are a named 'key' query parameter
     *
     * In "http://example.com/index?key=value&test=yes" the query parameters
     * are "key" and "test" for the values of "value" and "yes"
     *
     * @param key
     * @return true
     * @return false
     */
    virtual bool queryParameterExist(const std::string &key) const noexcept = 0;

    /**
     * @brief Return the query parameter "key" found in the route
     *
     * In "http://example.com/index?key=value&test=yes" the query parameters
     * are "key" and "test" for the values of "value" and "yes"
     * Throws a http::QueryParameterException if the parameter is not found
     *
     * @param key
     * @return std::string
     */
    virtual std::string queryParameter(const std::string &key) const = 0;

    /**
     * @brief Add / Update a query parameter
     *
     * In "http://example.com/index?key=value&test=yes" the query parameters
     * are "key" and "test" for the values of "value" and "yes"
     * Throws a http::QueryParameterException if the parameter is not valid
     *
     * @param key
     * @param value
     */
    virtual void queryParameter(std::string key, std::string value) = 0;

};

} // namespace http

#endif // IREQUEST_HPP
