#include <memory>
#include <boost/bind.hpp>
#include "BoostNetworkServer.hpp"

zia::net::BoostNetworkServer::BoostNetworkServer(unsigned short port) :
m_socket(m_io), m_acceptor(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), m_networkManager()
{
    bindAcceptor();
}

zia::net::BoostNetworkServer::~BoostNetworkServer()
{

}

void zia::net::BoostNetworkServer::run()
{
    this->m_io.run();
}

void zia::net::BoostNetworkServer::bindAcceptor()
{
    boost::shared_ptr<zia::net::BoostNetworkClient> connection(new zia::net::BoostNetworkClient(this->m_acceptor, this->m_networkManager));
    auto binding = boost::bind(&BoostNetworkServer::acceptHandler, this, connection, boost::asio::placeholders::error);
    this->m_acceptor.async_accept(connection->getSocket(), binding);
}

void zia::net::BoostNetworkServer::acceptHandler(boost::shared_ptr<zia::net::BoostNetworkClient> connection, const boost::system::error_code &error)
{
    if (!error) {
        connection->bindRead();
        this->m_networkManager->newClient(connection);
    }
    else
        delete connection.get();
    bindAcceptor();
}
