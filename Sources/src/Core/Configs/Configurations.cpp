/**
 * @file Configurations.cpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief
 * @version 1.0
 * @date 2020-01-23
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>
#include "Configurations.hpp"

core::Configurations::Configurations(const std::string &filename)
{
    this->updatePath(filename);
}

core::Configurations::~Configurations()
{

}

void core::Configurations::updatePath(const std::string &filename)
{
    this->m_filename = filename;
    this->reload();
}

void core::Configurations::reload()
{
    // this->m_yml = std::make_unique<yconf::ConfigNode>(this->m_filename);

    // auto array = m_yml->getArray("hosts");
    // std::cout << array.size() << std::endl;

    // Load configs
    //

    /**
     * @brief Simple yaml config file parsing
     * Test file used :
     *

    martin:
    name: Martin D'vloper
    job: Developer
    age: 22
        job: Baker
    experience:
        duration: 2
    skills:
        - python
        - perl
        - pascal
    */

    // void test_config()
    // {
    //     try {
    //         std::unique_ptr<IConfigNode> config = std::make_unique<yconf::ConfigNode>("../../sample.yaml");
    //         config = config->getChild("martin");


    //         std::cout << "Config : martin age is " << yconf::helper::getAs<int>(*config, "age") << std::endl;
    //         std::cout << "Config : martin name is " << config->getValue("name") << std::endl;
    //         std::cout << "Config : martin.experience.job " << config->getValue("experience.job") << std::endl;
    //         std::cout << "Config : martin.experience.duration " << yconf::helper::getAs<int>(*config, "experience.duration") << std::endl;

    //         std::cout << "Config : martin.skills content is [ " << std::endl;
    //         for (const auto &field : config->getArray("skills"))
    //                 std::cout << "'" << field << "'" << std::endl;
    //         std::cout << "]" << std::endl;


    //     } catch (std::exception const &e) {
    //         std::cerr << "Error while testing config nodes : " << e.what() << std::endl;
    //     }
    // }
}
