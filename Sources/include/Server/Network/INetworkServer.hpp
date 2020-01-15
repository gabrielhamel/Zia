#pragma once

#include <string>

namespace zia::net
{

    class INetworkServer
    {
        public:
            virtual ~INetworkServer() = default;
            virtual void run() = 0;
    };

}
