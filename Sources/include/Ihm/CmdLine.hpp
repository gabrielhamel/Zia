/**
 * @file CmdLine.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-23
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CMD_LINE_HPP
#define CMD_LINE_HPP

#include "ListenersControl.hpp"

namespace ihm
{

class CmdLine
{

private:
    core::ListenersControl &m_control;

public:

    CmdLine(core::ListenersControl &control);

    ~CmdLine();

    void parseCommand(const std::vector<std::string> &cmd);

};

} // namespace ihm

#endif // CMD_LINE_HPP
