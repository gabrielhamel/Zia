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

static void listAllListeners(ihm::CmdLine *cmdLine, const std::vector<std::string> &params)
{
    auto vec = cmdLine->getController().listListeners();
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << std::to_string(i) << ". " << std::to_string(vec[i]) << std::endl;
}

static void help(ihm::CmdLine *cmdLine, const std::vector<std::string> &params)
{
    auto &cmds = cmdLine->getCommandsObject();
    for (auto &command : cmds)
        std::cout << command.name << "\t" << command.description << std::endl;
}

static void printConfigs(ihm::CmdLine *cmdLine, const std::vector<std::string> &params)
{
    cmdLine->getController().getConfigurations().print();
}

static void reloadConfigs(ihm::CmdLine *cmdLine, const std::vector<std::string> &params)
{
    try {
        cmdLine->getController().getConfigurations().reload();
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

static const std::vector<ihm::command_t> commands = {
    {"configs", 0, printConfigs, "Display whole configurations of the server"},
    {"exit", 0, NULL, "Close the interpreters and shutdown all listeners"},
    {"help", 0, help, "Display this helper"},
    {"list", 0, listAllListeners, "List all running listeners"},
    {"reload", 0, reloadConfigs, "Reload the configurations file"}
};

const std::vector<ihm::command_t> &ihm::CmdLine::getCommandsObject() const
{
    return commands;
}

ihm::CmdLine::CmdLine(core::ListenersControl &control) :
m_control(control)
{
    while (1) {
        auto tokens = promptUser();
        if (std::cin.eof())
            break;
        if (tokens.size() < 1)
            continue;
        if (tokens[0] == "exit" && tokens.size() == 1)
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

std::vector<std::string> ihm::CmdLine::promptUser() const
{
    std::cout << "> ";
    std::string tmp;
    std::getline(std::cin, tmp);
    std::vector<std::string> tokens;
    boost::split(tokens, tmp, boost::is_any_of(" "));
    std::vector<std::string> res;
    std::copy_if(tokens.begin(), tokens.end(), std::back_inserter(res), [] (const std::string &token) {
        return token.size();
    });
    return res;
}

core::ListenersControl &ihm::CmdLine::getController() const
{
    return this->m_control;
}

void ihm::CmdLine::parseCommand(const std::vector<std::string> &cmd)
{
    for (size_t i = 0; i < commands.size(); i++) {
        if (commands[i].name == cmd[0]) {
            if (commands[i].nbParams != cmd.size() - 1) {
                // error
                std::cerr << "Invalid params number" << std::endl;
            }
            else
                commands[i].function(this, std::vector<std::string>(cmd.begin() + 1, cmd.end()));
            break;
        }
        if (i == commands.size() - 1) {
            // error
            std::cerr << "Invalid command. You can type 'help' to see all commands" << std::endl;
            break;
        }
    }
}
