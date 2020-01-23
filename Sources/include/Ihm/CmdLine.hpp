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

class CmdLine;

typedef struct {
    const std::string name;
    std::size_t nbParams;
    void (*function)(ihm::CmdLine *, const std::vector<std::string> &);
    const std::string description;
} command_t;

/**
 * @brief Interact with the user by tokenized string
 *
 */
class CmdLine
{

private:

    /**
     * @brief The main zia controler
     *
     */
    core::ListenersControl &m_control;

    /**
     * @brief Interpret user commands
     *
     */
    void parseCommand(const std::vector<std::string> &cmd);

    /**
     * @brief wait an user entries and tokenize the cmd
     *
     */
    std::vector<std::string> promptUser() const;

public:

    /**
     * @brief Construct a new Cmd Line object
     *
     */
    CmdLine(core::ListenersControl &control);

    /**
     * @brief Destroy the Cmd Line object
     *
     */
    ~CmdLine();

    /**
     * @brief Get the Controller object
     *
     */
    core::ListenersControl &getController() const;

    /**
     * @brief Return the commands object
     *
     */
    const std::vector<ihm::command_t> &getCommandsObject() const;

};

} // namespace ihm

#endif // CMD_LINE_HPP
