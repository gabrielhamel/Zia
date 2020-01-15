#include "User.hpp"

zia::net::User::User(boost::shared_ptr<zia::net::INetworkClient> networkPart) :
m_networkPart(networkPart)
{

}

zia::net::User::~User()
{

}

boost::shared_ptr<zia::net::INetworkClient> zia::net::User::getNetworkPart() const
{
    return this->m_networkPart;
}
