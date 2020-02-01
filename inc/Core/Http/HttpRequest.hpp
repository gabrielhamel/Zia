/*
** EPITECH PROJECT, 2019
** HttpRequest.hpp
** File description:
** HttpRequest.hpp
*/

#pragma once

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#include "IRequest.hpp"

class HttpRequest : public http::IRequest
{
    private:
        http::Verb m_request_method;
        std::string m_route;
        std::string m_route_without_query;
        std::string m_protocol;
        std::vector<std::pair<std::string, std::string>> m_request_header;
        std::vector<std::pair<std::string, std::string>> m_cookie;
        std::vector<std::pair<std::string, std::string>> m_query_parameters;
        std::string m_body;

        void init_map();
        void get_request_method(std::string line);
        void set_query_parameters(std::string line) noexcept;
        void set_cookie(std::string line) noexcept;
        std::vector<std::pair<std::string, std::string>> get_query_parameters(std::string route) const;
    public:
        HttpRequest(std::string request);
        ~HttpRequest();

        http::Verb verb() const noexcept;
        bool verb(http::Verb verb) noexcept;
        std::string route() const noexcept;
        bool route(std::string route) noexcept;
        bool queryParameterExist(const std::string &key) const noexcept;
        std::string queryParameter(const std::string &key) const noexcept;
        bool queryParameter(std::string key, std::string value) noexcept;
        std::string cookie(const std::string &name) const noexcept;

        std::string protocol() const noexcept;
        bool headerParameterExist(const std::string &key) const noexcept;
        std::string headerParameter(const std::string &key) const noexcept;
        bool headerParameter(std::string key, std::string value) noexcept;
        std::string body() const noexcept;
        bool body(std::string body) noexcept;
        bool bodyAppend(std::string body) noexcept;
        std::string serialize() const noexcept;

        std::unordered_map<std::string, http::Verb> map_request_method;
        std::unordered_map<std::string, std::string> url_encode;
};
