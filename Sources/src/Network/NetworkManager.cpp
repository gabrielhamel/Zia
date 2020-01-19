#include <boost/algorithm/string.hpp>
#include "NetworkManager.hpp"

net::NetworkManager::NetworkManager()
{

}

net::NetworkManager::~NetworkManager()
{

}

void net::NetworkManager::newClient(boost::shared_ptr<net::INetworkClient> client)
{
    this->m_clients.push_back(std::make_shared<http::Client>(client));
}

void net::NetworkManager::removeClient(boost::shared_ptr<INetworkClient> client)
{
    for (auto elem : this->m_clients) {
        if (elem->getNetworkPart() == client) {
            auto ptr = elem;
            this->m_clients.erase(std::find(this->m_clients.begin(), this->m_clients.end(), elem));
            break;
        }
    }
}

void net::NetworkManager::recvData(boost::shared_ptr<net::INetworkClient> client, const std::string data)
{
    for (auto elem : this->m_clients) {
        if (elem->getNetworkPart() == client) {
            http::Parser::parse(*elem.get(), data);
            break;
        }
    }
}
