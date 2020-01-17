#ifndef IRESPONSE_HPP
#define IRESPONSE_HPP

#include "IBasicObject.hpp"

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
     *
     * @return int
     */
    virtual int statusCode() const noexcept = 0;

    /**
     * @brief Set the status code of the response
     *
     * In http response there are always status code like "200" or "404"
     * To describe if the request is executed correctly
     * This function will throw a http::StatusCodeException if the status code isn't valid
     *
     * @param statusCode
     */
    virtual void statusCode(int statusCode) = 0;

    /**
     * @brief Returns the status message of the response
     *
     * In http response there are always status message
     * after the status code like "200 OK" or "404 Not found"
     *
     * @return std::string
     */
    virtual std::string statusMessage() const noexcept = 0;

    /**
     * @brief Set the status message of the response
     *
     * In http response there are always status message
     * after the status code like "200 OK" or "404 Not found"
     * This function will throw a http::StatusMessageException if the status message isn't valid
     *
     * @param statusMessage
     */
    virtual void statusMessage(std::string statusMessage) = 0;

};

} // namespace http

#endif // IRESPONSE_HPP
