/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigFile.cpp
*/

#include <stdexcept>
#include <iostream>

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

std::vector<std::string> yconf::ConfigNode::getScalarArray(const std::string &name) const
{
    const auto &nodes = getNodeAs<std::vector<YAML::Node>>(name);

    std::vector<std::string> result;

    result.reserve(nodes.size());
    for (const auto &n : nodes)
        if (n.IsScalar())
            result.emplace_back(n.as<std::string>());

    return result;
}

std::vector<std::unique_ptr<IConfigNode>> yconf::ConfigNode::getNodeArray(const std::string &name) const
{
    std::vector<std::unique_ptr<IConfigNode>> result;
    std::vector<YAML::Node> nodes;
    try {
        nodes = getNodeAs<std::vector<YAML::Node>>(name);
    }
    catch (...) {
        return result;
    }
    result.reserve(nodes.size());
    for (const auto &n : nodes)
        result.emplace_back(std::make_unique<ConfigNode>(n));
    return result;
}

std::unordered_map<std::string,
                   std::string> yconf::ConfigNode::getAllScalarsOf(const std::string &name) const
{
    std::unordered_map<std::string, std::string> result;
    const auto &node = getNode(name);

    for (const auto &prop : node) {
        if (prop.second.IsScalar())
            result[prop.first.as<std::string>()] =
                prop.second.as<std::string>();
        else
            throw std::runtime_error("Non scalar value in node");
    }

    return result;
}

YAML::Node yconf::ConfigNode::getNode(const std::string &name) const
{
    auto childPath = util::split(name, '.');
    auto fieldName = childPath.back();
    childPath.erase(childPath.end() - 1);
    if (!childPath.empty())
        return getChild(childPath.begin(), childPath.end()).getNode(fieldName);

    try {
        return _root[fieldName];
    } catch (const YAML::RepresentationException &) {
        throw std::out_of_range(std::string("No such property '") + name + "'");
    }
}
