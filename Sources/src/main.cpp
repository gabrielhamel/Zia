#include <iostream>
#include "ListenersControl.hpp"
#include "CmdLine.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage:\n\t" << av[0] << " <configs.yml>" << std::endl;
        return 84;
    }
    try {
        auto listeners = new core::ListenersControl();
        listeners->addListeners(8080);
        auto cmdLine = new ihm::CmdLine(*listeners);
        delete cmdLine;
        delete listeners;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
