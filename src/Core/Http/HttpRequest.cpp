/*
** EPITECH PROJECT, 2019
** HttpRequest.cpp
** File description:
** HttpRequest.cpp
*/

#include "HttpRequest.hpp"
#include <iostream>

HttpRequest::HttpRequest(std::string request) : m_body("")
{
    init_map();
    size_t body_position = 0;
    std::vector<std::string> request_vector;
    std::string current_line = "";
    for (size_t size = 0; size < request.length(); size++) {
        if (request.at(size) == '\r' && request.at(size + 1) == '\n') {
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
        set_query_parameters(line[1].substr(line[1].find("?") + 1, line[1].length()));
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
    map_request_method["GET"] = http::GET;
    map_request_method["HEAD"] = http::HEAD;
    map_request_method["POST"] = http::POST;
    map_request_method["PUT"] = http::PUT;
    map_request_method["DELETE"] = http::DELETE;
    map_request_method["CONNECT"] = http::CONNECT;
    map_request_method["OPTIONS"] = http::OPTIONS;
    map_request_method["TRACE"] = http::TRACE;
    map_request_method["PATCH"] = http::PATCH;

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


void HttpRequest::set_query_parameters(std::string line) noexcept
{
    m_query_parameters = get_query_parameters(line);
}


std::vector<std::pair<std::string, std::string>> HttpRequest::get_query_parameters(std::string line) const
{
    std::vector<std::string> query_params;
    std::vector<std::pair<std::string, std::string>> query_params_final;
    size_t last_char = 0;
    for (size_t i = 1; i < line.size(); i++) {
        if (line.at(i) == '&') {
            query_params.push_back(line.substr(last_char, i));
            last_char = i + 1;
        }
    }
    query_params.push_back(line.substr(last_char, line.length()));
    for (auto &elem : query_params) {
        if (elem.find("=") == std::string::npos)
            throw std::runtime_error("Error with Query parameters");
        auto key = elem.substr(0, elem.find("="));
        auto value = elem.substr(elem.find("=") + 1, elem.length());
        for (auto &elem : url_encode)
            if (value.find(elem.first) != std::string::npos)
                value.replace(value.find(elem.first), elem.first.length(), elem.second);
        query_params_final.push_back(std::pair<std::string, std::string>(key, value));
    }

    return query_params_final;
}


http::Verb HttpRequest::verb() const noexcept
{
    return m_request_method;
}


bool HttpRequest::verb(http::Verb verb) noexcept
{
    if (verb > 9)
        return false;

    m_request_method = verb;

    return true;
}


std::string HttpRequest::route() const noexcept
{
    return m_route_without_query;
}


bool HttpRequest::route(std::string route) noexcept
{
    if (route == "" || route.at(0) != '/')
        return false;
    for (size_t i; i < route.length(); i++)
        if (i + 1 < route.length() && route.at(i) == '/' && route.at(i + 1) == '/')
            return false;

    m_route = route;
    m_route_without_query = route.substr(0, route.find("?"));
    if (route.find("?") != std::string::npos)
        set_query_parameters(route.substr(route.find("?") + 1, route.length()));
    
    return true;
}


bool HttpRequest::queryParameterExist(const std::string &key) const noexcept
{
    for (auto &elem : m_query_parameters)
        if (elem.first == key)
            return true;

    return false;
}


std::string HttpRequest::queryParameter(const std::string &key) const noexcept
{
    for (auto &elem : m_query_parameters)
        if (elem.first == key)
            return elem.second;

    return "";
}


bool HttpRequest::queryParameter(std::string key, std::string value) noexcept
{
    if (key == "" || value == "")
        return false;
    for (auto &elem : m_query_parameters) {
        if (elem.first == key) {
            elem.second = value;
            return true;
        }
    }
    m_query_parameters.emplace(m_query_parameters.end(), std::pair<std::string, std::string>(key, value));

    return true;
}


std::string HttpRequest::cookie(const std::string &name) const noexcept
{
    if (name == "")
        return "";
    for (auto &elem : m_request_header) {
        if (elem.first == "Cookie") {
            std::vector<std::string> line;
            boost::split(line, elem.second, boost::is_any_of(" "));
            for (auto &it : line) {
                auto key = it.substr(0, it.find("="));
                auto value = it.substr(it.find("=") + 1, it.length() - 1);
                if (key == name)
                    return value;
            }
        }
    }

    return "";
}


std::string HttpRequest::body() const noexcept
{
    return m_body;
}


bool HttpRequest::body(std::string body) noexcept
{
    if (body == "")
        return false;
    for (auto &elem : m_request_header) {
        if (elem.first == "Content-Length") {
            elem.second = std::to_string(std::stoi(elem.second) + body.length());
            m_body = body;
            return true;
        }
    }
    m_request_header.push_back(std::pair<std::string, std::string>("Content-Length", std::to_string(body.length())));
    m_body = body;

    return true;
}


bool HttpRequest::bodyAppend(std::string body) noexcept
{
    if (body == "")
        return false;
    for (auto &elem : m_request_header) {
        if (elem.first == "Content-Length") {
            elem.second = std::to_string(std::stoi(elem.second) + body.length());
            m_body += body;
            return true;
        }
    }
    m_request_header.push_back(std::pair<std::string, std::string>("Content-Length", std::to_string(body.length())));
    m_body += body;

    return true;
}


std::string HttpRequest::serialize() const noexcept
{
    std::string to_return = "";
    std::string query_params = "";
    for (auto &elem : map_request_method)
        if (elem.second == m_request_method)
            to_return += elem.first;
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

    to_return += "\r\n" + m_body;

    return to_return;
}


std::string HttpRequest::protocol() const noexcept
{
    return m_protocol;
}


bool HttpRequest::headerParameterExist(const std::string &key) const noexcept
{
    for (auto &elem : m_request_header)
        if (elem.first == key)
            return true;

    return false;
}


std::string HttpRequest::headerParameter(const std::string &key) const noexcept
{
    for (auto &elem : m_request_header)
        if (elem.first == key)
            return elem.second;

    return "";
}


bool HttpRequest::headerParameter(std::string key, std::string value) noexcept
{
    if (key == "" || value == "")
        return false;
    for (auto &elem : m_request_header) {
        if (elem.first == key) {
            elem.second = value;
            return true;
        }
        if (elem.second == value)
            return true;
    }

    m_request_header.emplace(m_request_header.end(), std::pair<std::string, std::string>(key, value));

    return true;
}
