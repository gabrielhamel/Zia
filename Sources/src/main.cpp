#include <iostream>
#include "ListenersControl.hpp"
#include "CmdLine.hpp"
#include "Configurations.hpp"

#include "yconf/ConfigNode.hpp"

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

void test_config()
{
    try {
        std::unique_ptr<IConfigNode> config = std::make_unique<yconf::ConfigNode>("../../sample.yaml");
        config = config->getChild("martin");


        std::cout << "Config : martin age is " << yconf::helper::getAs<int>(*config, "age") << std::endl;
        std::cout << "Config : martin name is " << config->getValue("name") << std::endl;
        std::cout << "Config : martin.experience.job " << config->getValue("experience.job") << std::endl;
        std::cout << "Config : martin.experience.duration " << yconf::helper::getAs<int>(*config, "experience.duration") << std::endl;

        std::cout << "Config : martin.skills content is [ " << std::endl;
        for (const auto &field : config->getArray("skills"))
                std::cout << "'" << field << "'" << std::endl;
        std::cout << "]" << std::endl;


    } catch (std::exception const &e) {
    }
        std::cerr << "Error while testing config nodes : " << e.what() << std::endl;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cerr << "Usage:\n\t" << av[0] << " <configs.yml>" << std::endl;
        return 84;
    }
    try {
        auto configs = std::make_unique<core::Configurations>(av[1]);
        auto listeners = std::make_unique<core::ListenersControl>(*configs);
        listeners->newListener(8080);
        auto cmdLine = std::make_unique<ihm::CmdLine>(*listeners);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
