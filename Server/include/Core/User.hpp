#pragma once

#include <boost/shared_ptr.hpp>
#include "INetworkClient.hpp"

namespace zia::net
{

    class User
    {
        private:
            boost::shared_ptr<zia::net::INetworkClient> m_networkPart;
        public:
            User(boost::shared_ptr<zia::net::INetworkClient> networkPart);
            ~User();
            boost::shared_ptr<zia::net::INetworkClient> getNetworkPart() const;
    };

}
