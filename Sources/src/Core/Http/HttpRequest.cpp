/*
** EPITECH PROJECT, 2019
** HttpRequest.cpp
** File description:
** HttpRequest.cpp
*/

#include "HttpRequest.hpp"

HttpRequest::HttpRequest(std::string request)
{
    //std::unordered_map<std::string, std::string> m_query_parameters;
    std::string::size_type size = 0;
    int i = 0;
    
    for (auto end = 0; (end = request.find("\r\n", end)) != std::string::npos; end++, i++, size = end + 2) {
        std::string tmp = request.substr(i, end - i);
        if (i == 0) {
            get_request_method(tmp);
            std::vector<std::string> line;
            boost::split(line, tmp, boost::is_any_of(" "));
            if (line.size() < 2)
                throw std::runtime_error("Error no route or no protocol or no request method");
            m_route = line[1];
            m_route_without_query = line[1].substr(0, line[1].find("?"));
            m_protocol = line[2];
            line.clear();
            boost::split(line, tmp, boost::is_any_of("?"));
            if (line.size() < 2)
                get_query_parameters(tmp);
        }
        else {
            if (tmp.find(": ") == std::string::npos)
                throw std::runtime_error("String not type of key: value");
            m_request_header[tmp.substr(0, tmp.find(": "))] = tmp.substr(tmp.find(": "), tmp.length());
        }
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

void HttpRequest::get_query_parameters(std::string line)
{
    std::unordered_map<std::string, std::string> url_encode;
    url_encode["%%0A"] = "\n";
    url_encode["%%0D"] = "\n";
    url_encode["%%0D%%0A"] = "\n";
    url_encode["%%20"] = " ";
    url_encode["%%21"] = "!";
    url_encode["%%22"] = "\"";
    url_encode["%%23"] = "#";
    url_encode["%%24"] = "$";
    url_encode["%%25"] = "%%";
    url_encode["%%26"] = "&";
    url_encode["%%27"] = "'";
    url_encode["%%28"] = "(";
    url_encode["%%29"] = ")";
    url_encode["%%2A"] = "*";
    url_encode["%%2B"] = "+";
    url_encode["%%2C"] = ",";
    url_encode["%%2D"] = "-";
    url_encode["%%2E"] = ".";
    url_encode["%%2F"] = "/";
    url_encode["%%3A"] = ":";
    url_encode["%%3B"] = ";";
    url_encode["%%3C"] = "<";
    url_encode["%%3D"] = "=";
    url_encode["%%3E"] = ">";
    url_encode["%%3F"] = "?";
    url_encode["%%40"] = "@";
    url_encode["%%5B"] = "[";
    url_encode["%%5C"] = "\\";
    url_encode["%%5D"] = "]";
    url_encode["%%5E"] = "^";
    url_encode["%%5F"] = "_";
    url_encode["%%60"] = "`";
    url_encode["%%7B"] = "{";
    url_encode["%%7C"] = "|";
    url_encode["%%7D"] = "}";
    url_encode["%%7E"] = "~";    
    for (size_t i = 1; i < line.size(); i++) {
        
    }

}


std::string HttpRequest::to_string() const
{
    
}
