/*
** EPITECH PROJECT, 2019
** zia_project
** File description:
** testModuleInterface.hpp
*/

#pragma once

class ModuleApi
{
public:
    virtual ~ModuleApi() = default;

public:
    virtual void sayHello() const = 0;
};
