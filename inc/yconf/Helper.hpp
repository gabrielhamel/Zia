/*
** EPITECH PROJECT, 2019
** zia_project
** File description:
** Helper.hpp
*/

#pragma once

#include <boost/lexical_cast.hpp>
#include "IConfigNode.hpp"

namespace yconf::helper {

template <typename T>
T getAs(const IConfigNode &node, const std::string &fieldName)
{
    return boost::lexical_cast<T>(node.getValue(fieldName));
}

template <typename T>
T getAsOrDefault(const IConfigNode &node, const std::string &fieldName, T defaultValue)
{
    try {
        return boost::lexical_cast<T>(node.getValue(fieldName));
    } catch (const std::out_of_range &) {
        return defaultValue;
    }
}

}
