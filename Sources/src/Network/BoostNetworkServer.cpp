#include <memory>
#include <boost/bind.hpp>
#include "BoostNetworkServer.hpp"

net::BoostNetworkServer::BoostNetworkServer(unsigned short port, core::Configurations &configs) :
m_socket(m_io), m_acceptor(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), m_networkManager(configs)
{
    bindAcceptor();
}

net::BoostNetworkServer::~BoostNetworkServer()
{

}

void net::BoostNetworkServer::run()
{
    this->m_io.run();
}

void net::BoostNetworkServer::stop()
{
    this->m_io.stop();
}

void net::BoostNetworkServer::bindAcceptor()
{
    boost::shared_ptr<net::BoostNetworkClient> connection(new net::BoostNetworkClient(this->m_acceptor, this->m_networkManager));
    auto binding = boost::bind(&BoostNetworkServer::acceptHandler, this, connection, boost::asio::placeholders::error);
    this->m_acceptor.async_accept(connection->getSocket(), binding);
}

void net::BoostNetworkServer::acceptHandler(boost::shared_ptr<net::BoostNetworkClient> connection, const boost::system::error_code &error)
{
    if (!error) {
        connection->bindRead();
        this->m_networkManager.newClient(connection);
    }
    else
        delete connection.get();
    bindAcceptor();
}
