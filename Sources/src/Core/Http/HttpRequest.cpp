/*
** EPITECH PROJECT, 2019
** HttpRequest.cpp
** File description:
** HttpRequest.cpp
*/

#include "HttpRequest.hpp"

HttpRequest::HttpRequest(std::string request) : m_body("")
{
    init_map();
    size_t body_position = 0;
    std::vector<std::string> request_vector;
    std::string current_line = "";
    for (size_t size = 0; size < request.length(); size++) {
        if (request.at(size) == '\r' and request.at(size + 1) == '\n') {
            request_vector.push_back(current_line);
            size += 1;
            current_line = "";
        }
        else
            current_line += request.at(size);
    }
    for (auto it = request_vector.begin(); it != request_vector.end(); it++)
        if ((*it) == "")
            body_position = std::distance(request_vector.begin(), it);
    
    auto &elem = request_vector[0];
    get_request_method(elem);
    std::vector<std::string> line;
    boost::split(line, elem, boost::is_any_of(" "));
    if (line.size() != 3)
        throw std::runtime_error("Error no route or no protocol or no request method or more parameters");
    m_route = line[1];
    m_route_without_query = line[1].substr(0, line[1].find("?"));
    m_protocol = line[2];
    if (line[1].find("?") != std::string::npos)
        get_query_parameters(line[1].substr(line[1].find("?") + 1, line[1].length()));
    std::for_each(request_vector.begin() + 1, request_vector.end() - (request_vector.size() - body_position), [this](auto &elem) {
        if (elem.find(": ") == std::string::npos)
            throw std::runtime_error("String not type of key: value");
        auto key = elem.substr(0, elem.find(": "));
        auto value = elem.substr(elem.find(": ") + 2, elem.length());
        m_request_header.emplace(m_request_header.end(), std::pair<std::string, std::string>(key, value));
    });

    if (body_position != 0 && body_position < request_vector.size())
        std::for_each(request_vector.begin() + body_position + 1, request_vector.end(), [this](auto &elem) {
            m_body += elem;
        });
}

HttpRequest::~HttpRequest() {}

void HttpRequest::init_map()
{
    map_request_method["GET"] = GET;
    map_request_method["HEAD"] = HEAD;
    map_request_method["POST"] = POST;
    map_request_method["PUT"] = PUT;
    map_request_method["DELETE"] = DELETE;
    map_request_method["CONNECT"] = CONNECT;
    map_request_method["OPTIONS"] = OPTIONS;
    map_request_method["TRACE"] = TRACE;
    map_request_method["PATCH"] = PATCH;

    url_encode["%0A"] = "\n";
    url_encode["%0D"] = "\n";
    url_encode["%0D%0A"] = "\n";
    url_encode["%20"] = " ";
    url_encode["%21"] = "!";
    url_encode["%22"] = "\"";
    url_encode["%23"] = "#";
    url_encode["%24"] = "$";
    url_encode["%25"] = "%%";
    url_encode["%26"] = "&";
    url_encode["%27"] = "'";
    url_encode["%28"] = "(";
    url_encode["%29"] = ")";
    url_encode["%2A"] = "*";
    url_encode["%2B"] = "+";
    url_encode["%2C"] = ",";
    url_encode["%2D"] = "-";
    url_encode["%2E"] = ".";
    url_encode["%2F"] = "/";
    url_encode["%3A"] = ":";
    url_encode["%3B"] = ";";
    url_encode["%3C"] = "<";
    url_encode["%3D"] = "=";
    url_encode["%3E"] = ">";
    url_encode["%3F"] = "?";
    url_encode["%40"] = "@";
    url_encode["%5B"] = "[";
    url_encode["%5C"] = "\\";
    url_encode["%5D"] = "]";
    url_encode["%5E"] = "^";
    url_encode["%5F"] = "_";
    url_encode["%60"] = "`";
    url_encode["%7B"] = "{";
    url_encode["%7C"] = "|";
    url_encode["%7D"] = "}";
    url_encode["%7E"] = "~";
}

void HttpRequest::get_request_method(std::string line)
{
    std::string request_method = line.substr(0, line.find(" "));

    auto res = map_request_method.find(request_method);
    if (res == map_request_method.end())
        throw std::runtime_error("Request method unknown");
    m_request_method = (*res).second;
}

void HttpRequest::get_query_parameters(std::string line)
{
    std::vector<std::string> query_params;
    size_t last_char = 0;
    for (size_t i = 1; i < line.size(); i++) {
        if (line.at(i) == '&') {
            query_params.push_back(line.substr(last_char, i));
            last_char = i + 1;
        }
    }
    query_params.push_back(line.substr(last_char, line.length()));
    std::for_each(query_params.begin(), query_params.end(), [this](auto &elem) {
        if (elem.find("=") == std::string::npos)
            throw std::runtime_error("Error with Query parameters");
        auto key = elem.substr(0, elem.find("="));
        auto value = elem.substr(elem.find("=") + 1, elem.length());
        for (auto &elem : url_encode)
            if (value.find(elem.first) != std::string::npos)
                value.replace(value.find(elem.first), elem.first.length(), elem.second);
        m_query_parameters.push_back(std::pair<std::string, std::string>(key, value));
    });
}


std::string HttpRequest::to_string()
{
    std::string to_return = "";
    std::string query_params = "";
    for (auto &elem : map_request_method) {
        if (elem.second == m_request_method)
            to_return += elem.first;
    }
    if (m_query_parameters.size() > 0)
        query_params = "?";
    for (auto &elem : m_query_parameters) {
        auto value = elem.second;
        if (value.find(elem.second) != std::string::npos)
            value.replace(value.find(elem.second), elem.second.length(), elem.first);
        query_params += "&" + elem.first + "=" + elem.second;
    }
    to_return += " " + m_route_without_query + query_params + " " + m_protocol + "\r\n";

    for (auto &elem : m_request_header)
        to_return += elem.first + ": " + elem.second + "\r\n";
    
    to_return += "\r\n" + m_body + "\r\n";

    return (to_return);
}


http::Verb HttpRequest::verb() const noexcept
{

}


void HttpRequest::verb(http::Verb verb)
{

}


std::string HttpRequest::route() const noexcept
{

}


void HttpRequest::route(std::string route)
{

}


bool HttpRequest::queryParameterExist(const std::string &key) const noexcept
{

}


std::string HttpRequest::queryParameter(const std::string &key) const
{

}


void HttpRequest::queryParameter(std::string key, std::string value)
{

}


std::string HttpRequest::cookie(const std::string &name) const
{

}
