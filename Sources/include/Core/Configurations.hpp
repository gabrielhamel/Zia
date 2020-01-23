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

public:

    Configurations(const std::string &filename);

    ~Configurations();

};

} // namespace core

#endif // CONFIGURATIONS_HPP
