/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigFile.hpp
*/

#pragma once

#include <vector>

#include "yaml-cpp/yaml.h"
#include "IConfigNode.hpp"
#include "util.hpp"

namespace yconf {

class ConfigNode : public IConfigNode
{
public:
    /**
     * @brief Config with no fields
     */
    ConfigNode() = default;
    explicit ConfigNode(const std::string &filePath);

    std::unique_ptr<IConfigNode> getChild(const std::string &name) const override;
    std::string getValue(const std::string &name) const override;
    std::vector<std::string> getArray(const std::string &name) const override;

private:
    explicit ConfigNode(const YAML::Node &root);

    ConfigNode getChild(std::vector<std::string>::const_iterator it, const std::vector<std::string>::const_iterator &endIt) const;

    template <typename T>
    T getNodeAs(const std::string &name) const;

private:
    const YAML::Node _root;
};


template<typename T>
T yconf::ConfigNode::getNodeAs(const std::string &name) const
{
    auto childPath = util::split(name, '.');
    auto fieldName = childPath.back();

    childPath.erase(childPath.end());
    if (not childPath.empty())
        return getChild(childPath.begin(), childPath.end()).getNodeAs<T>(fieldName);

    try {
        return _root[fieldName].as<T>();
    } catch (const YAML::RepresentationException &) {
        throw std::out_of_range(std::string("No such property '") + name + "'");
    }}

}
