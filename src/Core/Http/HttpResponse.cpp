/*
** EPITECH PROJECT, 2019
** HttpResponse.cpp
** File description:
** HttpResponse.cpp
*/

#include <iostream>
#include <ctime>

#include "HttpResponse.hpp"

HttpResponse::HttpResponse(std::string response)
{
    std::vector<std::string> response_vector;
    size_t body_position = 0;
    std::string current_line = "";
    for (size_t size = 0; size < response.length() - 2; size++) {
        if (response.at(size) == '\r' && response.at(size + 1) == '\n') {
            response_vector.push_back(current_line);
            size += 1;
            current_line = "";
        }
        else
            current_line += response.at(size);
    }

    for (auto it = response_vector.begin(); it != response_vector.end(); it++)
        if ((*it) == "")
            body_position = std::distance(response_vector.begin(), it);

    auto &elem = response_vector.at(0);
    std::vector<std::string> line;
    boost::split(line, elem, boost::is_any_of(" "));
    if (line.size() < 3)
        throw std::runtime_error("Error no protocol or no status code or no status msg or missing one of them");
    m_protocol = line.at(0);
    m_status_code = std::stoi(line.at(1));
    if (m_status_code < 0)
        throw std::runtime_error("Status code less than 0");
    std::for_each(line.begin() + 2, line.end(), [this](auto &elem) {
        m_status_msg += elem + " ";
    });

    m_status_msg = m_status_msg.substr(0, m_status_msg.length() - 1);

    std::for_each(response_vector.begin() + 1, response_vector.end() - (response_vector.size() - body_position), [this](auto &elem) {
        if (elem.find(": ") == std::string::npos) {
            throw std::runtime_error("String not type of key: value");
        }
        auto key = elem.substr(0, elem.find(": "));
        auto value = elem.substr(elem.find(": ") + 2, elem.length());
        m_response_header.emplace(m_response_header.end(), std::pair<std::string, std::string>(key, value));
    });
    if (body_position != 0 && body_position < response_vector.size()) {
        auto it = response.find("\r\n\r\n");
        if (it != std::string::npos) {
            this->m_body = response.substr(it + 4);
            this->headerParameter("Content-Length", std::to_string(m_body.size()));
        }
    }
}

HttpResponse::HttpResponse()
{
    this->m_protocol = "HTTP/1.1";
    this->statusCode(200);
    this->statusMessage("OK");
    this->headerParameter("Server", "zia/1.0.0 (Gab is a monster)");
    time_t now = time(0);
    char buff[4096] = {0};
    #ifdef _WIN32
        tm gmt = {0};
        gmtime_s(&gmt, &now);
        strftime(buff, sizeof(buff), "%a, %d %b %Y %H:%M:%S GMT", &gmt);
    #else
        tm *gmt = gmtime(&now);
        strftime(buff, sizeof(buff), "%a, %d %b %Y %H:%M:%S GMT", gmt);
    #endif
    this->headerParameter("Date", buff);
    this->headerParameter("Content-Type", "text/html");
    this->headerParameter("Content-Length", "0");
    this->headerParameter("Connection", "keep-alive");
}

HttpResponse::~HttpResponse()
{

}


int HttpResponse::statusCode() const noexcept
{
    return m_status_code;
}


bool HttpResponse::statusCode(int statusCode) noexcept
{
    if (statusCode < 0)
        return false;

    m_status_code = statusCode;

    return true;
}


std::string HttpResponse::statusMessage() const noexcept
{
    return m_status_msg;
}


bool HttpResponse::statusMessage(std::string statusMessage) noexcept
{
    if (statusMessage == "")
        return false;

    m_status_msg = statusMessage;

    return true;
}


bool HttpResponse::setCookie(std::string name, std::string value, CookieOptions options) noexcept
{
    std::string final_value = "";
    if (name == "" || value == "")
        return false;

    for (auto &elem : m_response_header)
        if (elem.first == "Set-Cookie" && elem.second == name + "=" + value)
            return true;

    for (auto &elem : options)
        final_value += elem.first + "; " + elem.second;
    if (final_value != "")
        final_value += "; ";

    final_value += name + "=" + value;
    m_response_header.emplace(m_response_header.end(), std::pair<std::string, std::string>("Set-Cookie", final_value));
    return true;
}


std::string HttpResponse::protocol() const noexcept
{
    return m_protocol;
}


bool HttpResponse::headerParameterExist(const std::string &key) const noexcept
{
    for (auto &elem : m_response_header)
        if (elem.first == key)
            return true;

    return false;
}


std::string HttpResponse::headerParameter(const std::string &key) const noexcept
{
    for (auto &elem : m_response_header)
        if (elem.first == key)
            return elem.second;

    return "";
}


bool HttpResponse::headerParameter(std::string key, std::string value) noexcept
{
    if (key == "" || value == "")
        return false;
    for (auto &elem : m_response_header) {
        if (elem.first == key) {
            elem.second = value;
            return true;
        }
        if (elem.second == value)
            return true;
    }

    m_response_header.emplace(m_response_header.end(), std::pair<std::string, std::string>(key, value));
    return true;
}


std::string HttpResponse::body() const noexcept
{
    return m_body;
}


bool HttpResponse::body(std::string body) noexcept
{
    m_body = body;
    this->headerParameter("Content-Length", std::to_string(m_body.size()));
    return true;
}


bool HttpResponse::bodyAppend(std::string body) noexcept
{
    m_body += body;
    this->headerParameter("Content-Length", std::to_string(m_body.size()));
    return true;
}


std::string HttpResponse::serialize() const noexcept
{
    std::string to_return = "";
    to_return += m_protocol + " " + std::to_string(m_status_code) + " " + m_status_msg + "\r\n";
    for (auto &elem : m_response_header)
        to_return += elem.first + ": " + elem.second + "\r\n";
    to_return += "\r\n" + m_body;
    return to_return;
}
