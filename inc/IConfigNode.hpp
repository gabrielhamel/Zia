/*
** EPITECH PROJECT, 2019
** zia_project
** File description:
** IConfigNode.hpp
*/

#pragma once

#include <string>
#include <memory>
#include <unordered_map>

class IConfigNode
{
public:
    virtual ~IConfigNode() = default;

public:
    /**
     * @brief Gets a child node
     * @param name Name of the wanted child node
     * If the name contains dot (`.`), it will return the child of the child, and so on
     *
     * so `getChild("abc.def.xyz")` is the same as
     * `getChild("abc")->getChild("def")->getChild("xyz")`
     *
     * @return unique pointer to the child node
     * @throws `std::out_of_range` if no such child exists
     */
    virtual std::unique_ptr<IConfigNode> getChild(const std::string &name) const = 0;

    /**
     * @brief Gets the value of a property
     * @param name The name of the wanted property
     * If the name contains dot (`.`), it will get the child of the child,
     * and so on until the last field that is the value name
     *
     * so `getValue("abc.def.xyz")` is the same as
     * `getChild("abc.def")->getValue("xyz")`
     *
     * @return Property value
     * @throws `std::out_of_range` if no such property exists
     */
    virtual std::string getValue(const std::string &name) const = 0;

    /**
     * @brief Gets the content of the array
     * @param name The name of the wanted array
     * If the name contains dot (`.`), it will get the child of the child,
     * and so on until the last field that is the value name
     *
     * so `getArray("abc.def.xyz")` is the same as
     * `getChild("abc.def")->getArray("xyz")`
     *
     * @return Array content
     * @throws `std::out_of_range` if no such property exists
     */
    virtual std::vector<std::string> getArray(const std::string &name) const = 0;

    /**
     * @brief  Returns all the properties from the node
     */
    virtual std::unordered_map<std::string, std::string> getAllProperties() const = 0;

};
