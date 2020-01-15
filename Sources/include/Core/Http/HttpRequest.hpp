/*
** EPITECH PROJECT, 2019
** HttpRequest.hpp
** File description:
** HttpRequest.hpp
*/

#pragma once

#include <string>
#include <unordered_map>

class HttpRequest
{
    enum REQUEST_METHOD {
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
    private:
        REQUEST_METHOD m_request_method;
        std::string m_route;
        std::string m_route_without_query;
        std::string m_protocol;
        std::unordered_map<std::string, std::string> m_request_header;
    public:
        HttpRequest(std::string request);
        ~HttpRequest();

        std::string to_string() const;
};
