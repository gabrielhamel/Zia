/*
** EPITECH PROJECT, 2019
** dynloader_tester
** File description:
** InterfaceImpl.hpp
*/

#pragma once

#include "../Interface.hpp"

class InterfaceImpl : public ITestInterface
{
public:
    void sayHello() const override;
};
