/*
** EPITECH PROJECT, 2019
** HttpRequest.hpp
** File description:
** HttpRequest.hpp
*/

#pragma once

#include <algorithm>
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
        std::unordered_map<std::string, REQUEST_METHOD> map_request_method;
        REQUEST_METHOD m_request_method;
        std::string m_route;
        std::string m_route_without_query;
        std::string m_protocol;
        std::vector<std::pair<std::string, std::string>> m_request_header;
        std::vector<std::pair<std::string, std::string>> m_query_parameters;

        void get_request_method(std::string line);
        void get_query_parameters(std::string line);
    public:
        HttpRequest(std::string request);
        ~HttpRequest();

        std::string to_string();
};
