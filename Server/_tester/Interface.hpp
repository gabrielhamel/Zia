/*
** EPITECH PROJECT, 2019
** dynloader_tester
** File description:
** Interface.hpp
*/

#pragma once

class ITestInterface
{
public:
    virtual ~ITestInterface() = default;

public:
    virtual void sayHello() const = 0;
};
