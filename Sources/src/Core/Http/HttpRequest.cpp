/*
** EPITECH PROJECT, 2019
** HttpRequest.cpp
** File description:
** HttpRequest.cpp
*/

#include "HttpRequest.hpp"

HttpRequest::HttpRequest(std::string request)
{
    // std::string m_route;
    // std::string m_route_without_query;
    std::string::size_type i = 0;
    int tour_boucle = 0;
    
    for (auto end = 0; (end = request.find("\r\n", end)) != std::string::npos; end++) {
        std::string tmp = request.substr(i, end - i);
        i = end + 2;
        if (tour_boucle == 0) {
            get_request_method(tmp);
            m_protocol = tmp.substr(2, tmp.find(" "));
        }
        else {
            if (tmp.find(": ") == std::string::npos)
                throw std::runtime_error("String not type of key: value");
            m_request_header[tmp.substr(0, tmp.find(": "))] = tmp.substr(tmp.find(": "), tmp.length());
        }
        tour_boucle += 1;
    }
}

HttpRequest::~HttpRequest() {}

void HttpRequest::get_request_method(std::string line)
{
    std::string request_method = line.substr(0, line.find(" "));
    if (request_method == "GET")
        m_request_method = GET;
    else if (request_method == "HEAD")
        m_request_method = HEAD;
    else if (request_method == "POST")
         m_request_method = POST;
    else if (request_method == "PUT")
        m_request_method = PUT;
    else if (request_method == "DELETE")
        m_request_method = DELETE;
    else if (request_method == "CONNECT")
        m_request_method = CONNECT;
    else if (request_method == "OPTIONS")
        m_request_method = OPTIONS;
    else if (request_method == "TRACE")
        m_request_method = TRACE;
    else if (request_method == "PATCH")
        m_request_method = PATCH;
    else
        throw std::runtime_error("Request method unknown");
}


std::string HttpRequest::to_string() const
{
    
}
