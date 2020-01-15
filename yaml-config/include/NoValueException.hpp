/*
** EPITECH PROJECT, 2019
** Project
** File description:
** NoValueException.hpp
*/

#pragma once

#include <string>

namespace YAML {

class NoValueException : public std::exception
{
public:
    explicit NoValueException(const std::string &what);

    const char *what() const noexcept override;
private:
    std::string _what;
};
}
