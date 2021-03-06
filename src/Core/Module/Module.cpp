/*
** EPITECH PROJECT, 2019
** zia_project
** File description:
** Module.cpp
*/

#include <iostream>

#include "Module/Module.hpp"

Module::Module(const std::string &path) :
_lib(path), _alias(boost::dll::import_alias<ApiType *()>(_lib, "create_module")), _impl(_alias())
{
    assert(_impl);
}

Module::ApiType &Module::get()
{
    return *_impl;
}

const Module::ApiType &Module::get() const
{
    return *_impl;
}

Module::ApiType *Module::operator->()
{
    return _impl.get();
}

const Module::ApiType *Module::operator->() const
{
    return _impl.get();
}

const boost::dll::shared_library &Module::getLibrary() const
{
    return _lib;
}
