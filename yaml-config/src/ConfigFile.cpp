/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigFile.cpp
*/

#include "ConfigFile.hpp"

YAML::ConfigFile::ConfigFile(const std::string &filePath)
    : _root(YAML::LoadFile(filePath))
{}
