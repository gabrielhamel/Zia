#include "Client.hpp"

http::Client::Client(boost::shared_ptr<zia::net::INetworkClient> networkPart) :
m_networkPart(networkPart)
{

}

http::Client::~Client()
{

}

boost::shared_ptr<zia::net::INetworkClient> http::Client::getNetworkPart() const
{
    return this->m_networkPart;
}
