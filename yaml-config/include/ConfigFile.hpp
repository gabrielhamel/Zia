/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigFile.hpp
*/

#pragma once

#include <boost/optional.hpp>
#include <vector>

#include "util.hpp"
#include "yaml-cpp/yaml.h"
#include "NoValueException.hpp"

namespace YAML {

class ConfigFile
{
public:
    /**
     * @brief Config with no fields
     */
    ConfigFile() = default;
    explicit ConfigFile(const std::string &filePath);

    template<typename T>
    boost::optional<T> get(const std::string &name);

    template<typename T>
    T getOrDefault(const std::string &name, const T &defaultValue);

    template<typename T>
    T getOrThrow(const std::string &name);


private:
    const YAML::Node _root;
};


template<typename T>
boost::optional<T> ConfigFile::get(const std::string &name)
{
    std::vector<YAML::Node> nodes{_root}; // iterating on the same YAML::Node object causes weird behavior

    for (const auto &field: util::split(name, '.')) {
        nodes.push_back(nodes.back()[field]);

        if (!nodes.back())
            return boost::none;
    }

    return nodes.back().as<T>();
}

template<typename T>
T ConfigFile::getOrDefault(const std::string &name, const T &defaultValue)
{
    auto result = get<T>(name);

    if (!result)
        return
            defaultValue;

    return result.get();
}

template<typename T>
T ConfigFile::getOrThrow(const std::string &name)
{
    auto result = get<T>(name);

    if (!result)
        throw NoValueException(name);

    return result.get();
}

}
