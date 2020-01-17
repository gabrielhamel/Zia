/*
** EPITECH PROJECT, 2019
** Project
** File description:
** NoValueException.cpp
*/

#include "yconf/NoValueException.hpp"

yconf::NoValueException::NoValueException(const std::string &what)
    : _what(std::string("No value for '") + what + "'")
{}

const char *yconf::NoValueException::what() const noexcept
{
    return _what.c_str();
}
