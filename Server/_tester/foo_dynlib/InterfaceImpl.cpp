/*
** EPITECH PROJECT, 2019
** dynloader_tester
** File description:
** InterfaceImpl.cpp
*/

#include <iostream>
#include "InterfaceImpl.hpp"

void InterfaceImpl::sayHello() const
{
    std::cout << "Hello from foo dyn library !" << std::endl;
}
