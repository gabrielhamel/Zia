/*
** EPITECH PROJECT, 2019
** Project
** File description:
** DynLoadingException.hpp
*/

#pragma once

#include <stdexcept>

class DLException : public std::exception
{
public:
    DLException();
    const char *what() const noexcept override;

private:
    std::string _what;
};


