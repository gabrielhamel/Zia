/*
** EPITECH PROJECT, 2019
** Project
** File description:
** Module.hpp
*/

#pragma once

#include <memory>
#include <functional>
#include <cassert>
#include <boost/dll.hpp>
#include <boost/function.hpp>

#include "ModuleApi.hpp"

/**
 * @brief Loads module from dynamic library.
 *
 * The dynamic library MUST provide the symbol `create_module` like
 *
 * \code
 * `ApiType` *create_module();
 * \endcode
 */
class Module
{
    using ApiType = ModuleApi;
public:
    explicit Module(const std::string &path);

    ApiType &get();
    const ApiType &get() const;

    ApiType *operator->();
    const ApiType *operator->() const;

private:
    std::unique_ptr<ApiType> _impl;
};


