#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

namespace http
{

/**
 * @brief Exception in case of query parameter not found or empty
 *
 */
struct QueryParameterException : public std::exception
{

    /**
     * @brief The error message
     *
     */
    const char *what() const noexcept
    {
        return "Invalid query parameter";
    }

};

/**
 * @brief Exception in case of header parameter not found or empty
 *
 */
struct HeaderParameterException : public std::exception
{

    /**
     * @brief The error message
     *
     */
    const char *what() const noexcept
    {
        return "Invalid header parameter";
    }

};

/**
 * @brief Exception in case of body not found or empty
 *
 */
struct BodyException : public std::exception
{

    /**
     * @brief The error message
     *
     */
    const char *what() const noexcept
    {
        return "Invalid body";
    }

};

/**
 * @brief Exception in case of route not found or invalid
 *
 */
struct RouteException : public std::exception
{

    /**
     * @brief The error message
     *
     */
    const char *what() const noexcept
    {
        return "Invalid route";
    }

};

struct StatusCodeException : public std::exception
{

    /**
     * @brief The error message
     *
     */
    const char *what() const noexcept
    {
        return "Invalid status code";
    }

};

struct StatusMessageException : public std::exception
{

    /**
     * @brief The error message
     *
     */
    const char *what() const noexcept
    {
        return "Invalid status message";
    }

};

struct CookieException : public std::exception
{
    /**
     * @brief The error message
     *
     */
    const char *what() const noexcept
    {
        return "Invalid cookie's name";
    }

};


} // namespace http

#endif // EXCEPTIONS_HPP
