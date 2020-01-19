#include <iostream>
#include "BoostNetworkServer.hpp"
#include "Module/Module.hpp"

/**
 * @brief Dead-simple module example
 */
void test_module()
{
    Module test("../../libtestMod.so");

    test->sayHello();
}


int main(int ac, char **av)
{
//    test_module();

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
