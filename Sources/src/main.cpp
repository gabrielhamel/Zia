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
}

/**
 * @brief Dead-simple yaml config file parsing
 */
void test_config()
{
    try {
        std::unique_ptr<IConfigNode> config = std::make_unique<yconf::ConfigNode>("../../sample.yaml");

        config = config->getChild("config");

        std::cout << "Config : port is " << yconf::helper::getAs<int>(*config, "port") << std::endl;
        std::cout << "Config : service/twitter/class is " << config->getValue("services.twitter.class") << std::endl;

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
        std::unique_ptr<net::INetworkServer> server(new net::BoostNetworkServer(std::stoi(av[1])));
        server->run();
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
