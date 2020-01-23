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

class TestModule : public module::ModuleApi
{
public:

    std::unique_ptr<http::IResponse> request(const http::IRequest &request)
    {
        std::cout << "Hello from TestModule !!" << std::endl;
    }

};

mod::ModuleApi *factory()
{
    return new TestModule;
}

BOOST_DLL_ALIAS(factory, create_module)
