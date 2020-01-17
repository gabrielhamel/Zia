/*
** EPITECH PROJECT, 2019
** Project
** File description:
** main.cpp
*/

#include <iostream>
#include <memory>
#include "ModuleApi.hpp"
#include "boost/dll/alias.hpp"

class TestModule : public ModuleApi
{
public:
    void sayHello() const override
    {
        std::cout << "Hello from TestModule !!" << std::endl;
    }
};

ModuleApi *factory()
{
    return new TestModule;
}

int foo = 42;

BOOST_DLL_ALIAS(factory, create_module)
