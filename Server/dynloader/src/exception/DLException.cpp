/*
** EPITECH PROJECT, 2019
** Project
** File description:
** DynLoadingException.cpp
*/

#include <dlfcn.h>
#include "exception/DLException.hpp"

DLException::DLException()
    : _what(dlerror())
{}

const char *DLException::what() const noexcept
{
    return _what.c_str();
}
