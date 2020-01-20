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

private:
    explicit ConfigNode(const YAML::Node &root);

    std::unique_ptr<IConfigNode> getChild(std::vector<std::string>::const_iterator it, const std::vector<std::string>::const_iterator &endIt) const;

private:
    const YAML::Node _root;
};

}
