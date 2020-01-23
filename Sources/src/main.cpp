#include <iostream>
#include "ListenersControl.hpp"
#include "CmdLine.hpp"
#include "Configurations.hpp"

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
