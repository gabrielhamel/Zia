/**
 * @file Configurations.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-23
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef CONFIGURATIONS_HPP
#define CONFIGURATIONS_HPP

#include <string>

namespace core {

class Configurations
{

private:

    std::string m_filename;

public:

    Configurations(const std::string &filename);

    ~Configurations();

    void updatePath(const std::string &filename);

    void reload();

};

} // namespace core

#endif // CONFIGURATIONS_HPP
