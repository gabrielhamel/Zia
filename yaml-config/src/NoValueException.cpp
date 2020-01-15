/*
** EPITECH PROJECT, 2019
** Project
** File description:
** NoValueException.cpp
*/

#include "NoValueException.hpp"

YAML::NoValueException::NoValueException(const std::string &what)
    : _what(std::string("No value for '") + what + "'")
{}

const char *YAML::NoValueException::what() const noexcept
{
    return _what.c_str();
}
