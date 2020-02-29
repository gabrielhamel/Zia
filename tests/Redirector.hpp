/**
 * @file Redirector.hpp
 * @author Gabriel Hamel (gabriel.hamel.pro@gmail.com)
 * @version 1.0
 * @date 2020-02-29
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef REDIRECTOR_HPP
#define REDIRECTOR_HPP

#include <ostream>
#include <iostream>

/**
 * @brief Redirect ostream to get their content
 *
 */
class Redirector
{

private:

    std::ostringstream m_oss;

    std::streambuf *m_backup;

    std::ostream &m_toSave;

public:

    Redirector(std::ostream &stream) :
    m_toSave(stream)
    {
        this->m_backup = stream.rdbuf();
        stream.rdbuf(this->m_oss.rdbuf());
    }

    ~Redirector()
    {
        this->m_toSave.rdbuf(this->m_backup);
    }

    std::string getContent()
    {
        this->m_oss << std::flush;
        return this->m_oss.str();
    }

};

#endif // REDIRECTOR_HPP
