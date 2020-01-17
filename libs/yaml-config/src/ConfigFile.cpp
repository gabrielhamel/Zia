/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigFile.cpp
*/

#include "yconf/ConfigFile.hpp"

yconf::ConfigFile::ConfigFile(const std::string &filePath)
    : _root(YAML::LoadFile(filePath))
{}
