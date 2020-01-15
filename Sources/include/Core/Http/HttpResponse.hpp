/*
** EPITECH PROJECT, 2019
** HttpResponse.hpp
** File description:
** HttpResponse.hpp
*/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Body.hpp"

class HttpResponse
{
    private:
        int m_status_code;
        std::string m_request;
        std::string m_status_msg;
        Body m_body;  
        std::vector<unsigned char> m_response;      
    public:
        HttpResponse(std::unordered_map<std::string, std::string> reponse);
};
