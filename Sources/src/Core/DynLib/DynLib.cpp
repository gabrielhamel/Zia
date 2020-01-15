/*
** EPITECH PROJECT, 2019
** Project
** File description:
** DynLib.cpp
*/

#include "DynLib.hpp"

DynLib::DynLib(const std::string &path) : _handle(dlopen(path.c_str(), RTLD_NOW))
{
    if (!_handle)
        throw DLException();
}

DynLib::~DynLib()
{
    dlclose(_handle);
}
