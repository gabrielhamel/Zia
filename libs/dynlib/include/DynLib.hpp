/*
** EPITECH PROJECT, 2019
** Project
** File description:
** DynLib.hpp
*/

#pragma once

#include <string>
#include <functional>
#include <dlfcn.h>
#include "DLException.hpp"

/**
 * @brief Representation of a library
 */
class DynLib
{
public:
    explicit DynLib(const std::string &path);
    virtual ~DynLib();

    template <typename T>
    T loadSymbol(const std::string &sym) const;

private:
    void *_handle;
};

template <typename T>
T DynLib::loadSymbol(const std::string &sym) const
{
    T result;
    *(void **)(&result) = dlsym(_handle, sym.c_str());

    if (!result)
        throw DLException();
    return result;
}
