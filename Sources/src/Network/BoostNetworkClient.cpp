#include <boost/bind.hpp>
#include "BoostNetworkClient.hpp"

net::BoostNetworkClient::BoostNetworkClient(boost::asio::basic_socket_acceptor<boost::asio::ip::tcp> &ec, NetworkManager &networkManager) :
m_socket(ec.get_executor()), m_connected(false), m_networkManager(networkManager)
{

}

net::BoostNetworkClient::~BoostNetworkClient()
{

}

boost::asio::ip::tcp::socket &net::BoostNetworkClient::getSocket()
{
    return this->m_socket;
}

void net::BoostNetworkClient::bindRead()
{
    if (this->m_connected == false)
        this->m_connected = true;
    auto binding = boost::bind(&BoostNetworkClient::readHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred);
    async_read_until(this->m_socket, this->m_buffer, "\0", binding);
}

std::size_t net::BoostNetworkClient::getId() const
{
    const BoostNetworkClient *ptr = this;
    return reinterpret_cast<std::size_t>(ptr);
}

void net::BoostNetworkClient::readHandler(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (error) {
        disconnect(error.message());
        return;
    }
    std::ostringstream ss;
    ss << &this->m_buffer;
    std::string message = ss.str();
    this->m_networkManager.recvData(shared_from_this(), message);
    bindRead();
}

void net::BoostNetworkClient::writeHandler(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (error)
        disconnect(error.message());
}

void net::BoostNetworkClient::send(const std::string &data)
{
    auto binding = boost::bind(&BoostNetworkClient::writeHandler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred);
    this->m_socket.async_write_some(boost::asio::buffer(data, data.length()), binding);
}

void net::BoostNetworkClient::disconnect(const std::string &message)
{
    this->m_networkManager.removeClient(shared_from_this());
    this->m_socket.close();
    this->m_connected = false;
}
