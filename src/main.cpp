#include <iostream>
#include "ListenersControl.hpp"
#include "CmdLine.hpp"
#include "Configurations.hpp"

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cerr << "Usage:\n\t" << av[0] << " <configs.yml>" << std::endl;
        return EXIT_FAILURE;
    }
    try {
        auto configs = std::make_unique<core::Configurations>(av[1]);
        auto listeners = std::make_unique<core::ListenersControl>(*configs);
        auto cmdLine = std::make_unique<ihm::CmdLine>(*listeners);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
