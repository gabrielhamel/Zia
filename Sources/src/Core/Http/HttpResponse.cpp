/*
** EPITECH PROJECT, 2019
** HttpResponse.cpp
** File description:
** HttpResponse.cpp
*/

#include <iostream>

#include "HttpResponse.hpp"

HttpResponse::HttpResponse(std::string response) : m_status_code(200), m_status_msg("OK")
{
    std::vector<std::string> response_vector;
    size_t body_position = 0;
    std::string current_line = "";
    for (size_t size = 0; size < response.length() - 2; size++) {
        if (response.at(size) == '\r' and response.at(size + 1) == '\n') {
            response_vector.push_back(current_line);
            size += 1;
            current_line = "";
        }
        else if (size + 1 == response.length() - 2)
            response_vector.push_back(current_line);
        else
            current_line += response.at(size);
    }

    for (auto it = response_vector.begin(); it != response_vector.end(); it++)
        if ((*it) == "")
            body_position = std::distance(response_vector.begin(), it);

    auto &elem = response_vector[0];
    std::vector<std::string> line;
    boost::split(line, elem, boost::is_any_of(" "));
    if (line.size() < 3)
        throw std::runtime_error("Error no protocol or no status code or no status msg or missing one of them");
    m_protocol = line[0];
    m_status_code = std::stoi(line[1]);
    if (m_status_code < 0)
        throw std::runtime_error("Status code less than 0");
    if (m_status_code != 200)
        m_status_msg = "";
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

    if (body_position != 0 && body_position < response_vector.size())
    std::for_each(response_vector.begin() + body_position + 1, response_vector.end(), [this](auto &elem) {
        m_body += elem;
    });
}


HttpResponse::~HttpResponse()
{

}


std::string HttpResponse::to_string()
{
    std::string to_return = "";
    to_return += m_protocol + " " + std::to_string(m_status_code) + " " + m_status_msg + "\r\n";
    for (auto &elem : m_response_header)
        to_return += elem.first + ": " + elem.second + "\r\n";
    to_return += "\r\n" + m_body + "\r\n";

    return to_return;
}


int HttpResponse::statusCode() const noexcept
{

}


void HttpResponse::statusCode(int statusCode)
{

}


std::string HttpResponse::statusMessage() const noexcept
{

}


void HttpResponse::statusMessage(std::string statusMessage)
{

}


bool HttpResponse::setCookie(std::string name, std::string value, CookieOptions options) noexcept
{

}
