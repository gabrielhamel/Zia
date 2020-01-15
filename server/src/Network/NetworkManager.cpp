#include <boost/algorithm/string.hpp>
#include "NetworkManager.hpp"

zia::net::NetworkManager::NetworkManager()
{

}

zia::net::NetworkManager::~NetworkManager()
{

}

void zia::net::NetworkManager::newClient(boost::shared_ptr<INetworkClient> client)
{
    this->m_clients.push_back(std::make_shared<User>(client));
}

void zia::net::NetworkManager::removeClient(boost::shared_ptr<INetworkClient> client)
{
    for (auto elem : this->m_clients) {
        if (elem->getNetworkPart() == client) {
            auto ptr = elem;
            this->m_clients.erase(std::find(this->m_clients.begin(), this->m_clients.end(), elem));
            break;
        }
    }
}

void zia::net::NetworkManager::recvData(boost::shared_ptr<zia::net::INetworkClient> client, const std::string data)
{
    for (auto elem : this->m_clients) {
        if (elem->getNetworkPart() == client) {
            zia::Parser::parse(elem, data);
            break;
        }
    }
}
