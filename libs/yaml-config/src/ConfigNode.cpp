/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigFile.cpp
*/

#include "yconf/ConfigNode.hpp"
#include "yconf/util.hpp"

yconf::ConfigNode::ConfigNode(const std::string &filePath)
    : ConfigNode(YAML::LoadFile(filePath))
{}

yconf::ConfigNode::ConfigNode(const YAML::Node &root)
    : _root(root)
{}

std::unique_ptr<IConfigNode> yconf::ConfigNode::getChild(const std::string &name) const
{
    const auto split = util::split(name, '.');

    return getChild(split.begin(), split.end());
}

std::unique_ptr<IConfigNode> yconf::ConfigNode::getChild(std::vector<std::string>::const_iterator it, const std::vector<std::string>::const_iterator &endIt) const
{
    try {
        auto node = _root[*it];

        if (node.IsDefined()) {
            auto next = it + 1;
            if (next == endIt)
                return std::unique_ptr<ConfigNode>(new ConfigNode(node));
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
    auto childPath = util::split(name, '.');
    auto fieldName = childPath.back();

    childPath.erase(childPath.end());
    if (not childPath.empty())
        return getChild(childPath.begin(), childPath.end())->getValue(fieldName);

    try {
        return _root[fieldName].as<std::string>();
    } catch (const YAML::RepresentationException &) {
        throw std::out_of_range(std::string("No such property '") + name + "'");
    }
}
