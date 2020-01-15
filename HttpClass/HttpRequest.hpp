/*
** EPITECH PROJECT, 2019
** HttpRequest.hpp
** File description:
** HttpRequest.hpp
*/

#pragma once

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class HttpRequest
{
    public:
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

        void get_request_method(std::string line);
    public:
        HttpRequest(std::string request);
        ~HttpRequest();

        std::string to_string() const;
};
