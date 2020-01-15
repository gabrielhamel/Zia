#pragma once

#include <string>

namespace zia::net
{

    class INetworkClient
    {
        public:
            virtual ~INetworkClient() = default;
            virtual void send(const std::string &data) = 0;
            virtual std::size_t getId() const = 0;
    };

}
