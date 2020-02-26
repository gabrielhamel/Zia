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
 * The dynamic library MUST provide a boost DLL alias `create_module` to a
 * function of signature
 *
 * \code
 * `ApiType` *create_module();
 * \endcode
 */
class Module
{
    using ApiType = module::Api;
public:
    explicit Module(const std::string &path);

    ApiType &get();
    const ApiType &get() const;

    ApiType *operator->();
    const ApiType *operator->() const;

    const boost::dll::shared_library &getLibrary() const;

private:
    boost::dll::shared_library _lib;
    std::unique_ptr<ApiType> _impl;
};
