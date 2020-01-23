/**
 * @file CmdLine.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-23
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>
#include <boost/algorithm/string.hpp>
#include "CmdLine.hpp"

ihm::CmdLine::CmdLine(core::ListenersControl &control) :
m_control(control)
{
    std::string tmp;

    while (1) {
        std::cout << "> ";
        std::getline(std::cin, tmp);
        std::vector<std::string> tokens;
        boost::split(tokens, tmp, boost::is_any_of(" "));
        if (tokens.size() < 1)
            continue;
        if (tokens[0] == "exit" || std::cin.eof())
            break;
        else
            parseCommand(tokens);
    }
    if (std::cin.eof())
        std::cout << "exit" << std::endl;
}

ihm::CmdLine::~CmdLine()
{

}

void ihm::CmdLine::parseCommand(const std::vector<std::string> &cmd)
{
    std::cout << "...parse..." << std::endl;
}
