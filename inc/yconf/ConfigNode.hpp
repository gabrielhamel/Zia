/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ConfigFile.hpp
*/

#pragma once

#include <vector>
#include <yaml-cpp/yaml.h>

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
    explicit ConfigNode(const YAML::Node &root);

    std::unique_ptr<IConfigNode> getChild(const std::string &name) const override;
    std::string getValue(const std::string &name) const override;
    std::vector<std::string> getScalarArray(const std::string &name) const override;
    std::vector<std::unique_ptr<IConfigNode>> getNodeArray(const std::string &name) const override;
    std::unordered_map<std::string,
                       std::string> getAllScalarsOf(const std::string &name) const override;

private:

    ConfigNode getChild(std::vector<std::string>::const_iterator it,
                        const std::vector<std::string>::const_iterator &endIt) const;

    template<typename T>
    T getNodeAs(const std::string &name) const;
    YAML::Node getNode(const std::string &name) const;

private:
    const YAML::Node _root;
};

template<typename T>
T yconf::ConfigNode::getNodeAs(const std::string &name) const
{
    return getNode(name).as<T>();
}

}
