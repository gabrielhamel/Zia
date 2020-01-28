/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigFile.cpp
*/

#include "yconf/ConfigNode.hpp"

yconf::ConfigNode::ConfigNode(const std::string &filePath)
    : ConfigNode(YAML::LoadFile(filePath))
{}

yconf::ConfigNode::ConfigNode(const YAML::Node &root)
    : _root(root)
{}

std::unique_ptr<IConfigNode> yconf::ConfigNode::getChild(const std::string &name) const
{
    const auto split = util::split(name, '.');

    return std::make_unique<ConfigNode>(getChild(split.begin(), split.end()));
}

yconf::ConfigNode yconf::ConfigNode::getChild(std::vector<std::string>::const_iterator it,
                                              const std::vector<std::string>::const_iterator &endIt) const
{
    try {
        auto node = _root[*it];

        if (node.IsDefined()) {
            auto next = it + 1;
            if (next == endIt)
                return ConfigNode{node};
            else
                return ConfigNode(node).getChild(next, endIt);
        }
    } catch (const YAML::RepresentationException &) {
        // throws after catch block, to also throws if try block does not return
    } catch (...) {
        throw;
    }
    throw std::out_of_range(
        std::string("No such child node '") + *it + "'");
}

std::string yconf::ConfigNode::getValue(const std::string &name) const
{
    return getNodeAs<std::string>(name);
}

std::vector<std::string> yconf::ConfigNode::getArray(const std::string &name) const
{
    return getNodeAs<std::vector<std::string>>(name);
}

std::unordered_map<std::string,
                   std::string> yconf::ConfigNode::getAllProperties() const
{
    std::unordered_map<std::string, std::string> result;

    for (const auto &prop : _root)
        if (prop.second.IsScalar())
            result[prop.first.as<std::string>()] = prop.second.as<std::string>();

    return result;
}
