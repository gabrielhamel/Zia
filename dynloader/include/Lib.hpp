/*
** EPITECH PROJECT, 2019
** Project
** File description:
** DynLib.hpp
*/

#pragma once

#include <memory>
#include "DynLib.hpp"

/**
 * @brief A dynamic library that provide a "make" symbol, returning a pointer
 * to an implementation of the Tinterface interface
 */
template <typename Tinterface>
class Lib : public DynLib
{
public:
    explicit Lib(const std::string &path);

    Tinterface &get()
    {
        return *_impl;
    }

    const Tinterface &get() const
    {
        return *_impl;
    }
private:
    std::unique_ptr<Tinterface> _impl;
};

template<typename Tinterface>
Lib<Tinterface>::Lib(const std::string &path)
    : DynLib(path), _impl(loadSymbol<Tinterface *(*)()>("make")())
{}
