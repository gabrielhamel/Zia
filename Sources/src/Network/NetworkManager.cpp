#include <boost/algorithm/string.hpp>
#include "NetworkManager.hpp"

net::NetworkManager::NetworkManager()
{

}

net::NetworkManager::~NetworkManager()
{

}

void net::NetworkManager::newClient(boost::shared_ptr<net::IClient> client)
{

}

void net::NetworkManager::removeClient(boost::shared_ptr<IClient> client)
{

}

void net::NetworkManager::recvData(boost::shared_ptr<net::IClient> client, const std::string &data)
{
    net::Request::execute(*client.get(), data);
}
