/*
** EPITECH PROJECT, 2019
** HttpRequest.cpp
** File description:
** HttpRequest.cpp
*/

#include "HttpRequest.hpp"

HttpRequest::HttpRequest(std::string request)
{
    REQUEST_METHOD m_request_method;
    std::string m_route;
    std::string m_route_without_query;
    std::string m_protocol;
    std::unordered_map<std::string, std::string> m_request_header;
}

HttpRequest::~HttpRequest() {}

std::string HttpRequest::to_string() const
{
    
}
