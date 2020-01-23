#include <iostream>
#include "BoostNetworkServer.hpp"
#include "Module/Module.hpp"
#include "yconf/ConfigNode.hpp"
#include "yconf/Helper.hpp"

/**
 * @brief Dead-simple module example
 */
void test_module()
{
    Module test("../../libtestMod.so");

    test->sayHello();
}

/**
 * @brief Simple yaml config file parsing
 *
 * Test file used :

martin:
  name: Martin D'vloper
  job: Developer
  age: 22
  experience:
    job: Baker
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

        std::cout << "Config : martin name is " << config->getValue("name") << std::endl;
        std::cout << "Config : martin age is " << yconf::helper::getAs<int>(*config, "age") << std::endl;
        std::cout << "Config : martin.experience.job " << config->getValue("experience.job") << std::endl;
        std::cout << "Config : martin.experience.duration " << yconf::helper::getAs<int>(*config, "experience.duration") << std::endl;

        std::cout << "Config : martin.skills content is [ " << std::endl;
        for (const auto &field : config->getArray("skills"))
                std::cout << "'" << field << "'" << std::endl;
        std::cout << "]" << std::endl;


    } catch (std::exception const &e) {
        std::cerr << "Error while testing config nodes : " << e.what() << std::endl;
    }
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage:\n\t" << av[0] << " <port>" << std::endl;
        return 84;
    }
    try {
        std::unique_ptr<zia::net::INetworkServer> server(new zia::net::BoostNetworkServer(std::stoi(av[1])));
        server->run();
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
