/*
** EPITECH PROJECT, 2019
** HttpResponse.hpp
** File description:
** HttpResponse.hpp
*/

#pragma once

#include <boost/algorithm/string.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "IResponse.hpp"

class HttpResponse : public http::IResponse
{
    private:
        int m_status_code;
        std::string m_status_msg;
        std::string m_body;
        std::string m_protocol;
        std::vector<std::pair<std::string, std::string>> m_response_header;

    public:
        HttpResponse(std::string response);
        ~HttpResponse();

        std::string to_string();

        int statusCode() const noexcept;
        bool statusCode(int statusCode) noexcept;
        std::string statusMessage() const noexcept;
        bool statusMessage(std::string statusMessage) noexcept;
        bool setCookie(std::string name, std::string value, CookieOptions options = CookieOptions()) noexcept;

        std::string protocol() const noexcept;
        bool headerParameterExist(const std::string &key) const noexcept;
        std::string headerParameter(const std::string &key) const noexcept;
        bool headerParameter(std::string key, std::string value) noexcept;
        std::string body() const noexcept;
        bool body(std::string body) noexcept;
        bool bodyAppend(std::string body) noexcept;
        std::string serialize() const noexcept;
};
