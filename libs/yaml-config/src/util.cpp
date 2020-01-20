/*
** EPITECH PROJECT, 2019
** Project
** File description:
** util.cpp
*/

#include <sstream>
#include "yconf/util.hpp"

std::vector<std::string> yconf::util::split(const std::string &str, char delimiter)
{
    std::stringstream ss{str};
    std::vector<std::string> result;
    std::string buff;

    while (std::getline(ss, buff, delimiter))
        result.emplace_back(std::move(buff));

    return result;
}
