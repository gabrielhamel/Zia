#include <iostream>
#include "BoostNetworkServer.hpp"

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
