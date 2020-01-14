/*
** EPITECH PROJECT, 2019
** Project
** File description:
** main.cpp
*/

#include <iostream>
#include "Interface.hpp"
#include "Lib.hpp"

void safeMain()
{
    // NOTE: You might want to adjust this path to wherever you compiled it
    Lib<ITestInterface> toto("../libfoo.so");

    toto.get().sayHello();
}

int main(int ac, char **av)
{
    try {
        safeMain();
    } catch (const std::exception &e) {
        std::cerr << "FATAL: " << e.what() << std::endl;
    }
}
