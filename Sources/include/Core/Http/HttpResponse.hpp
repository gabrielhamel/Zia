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

class HttpResponse
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
        void statusCode(int statusCode);
        std::string statusMessage() const noexcept;
        void statusMessage(std::string statusMessage);
        bool setCookie(std::string name, std::string value, CookieOptions options = CookieOptions()) noexcept;
};
