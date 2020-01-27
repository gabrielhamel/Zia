#include <boost/bind.hpp>
#include "BoostNetworkClient.hpp"

using namespace boost::asio;

net::BoostNetworkClient::BoostNetworkClient(basic_socket_acceptor<ip::tcp> &ec, NetworkManager &networkManager) :
m_socket(ec.get_executor()), m_connected(false), m_networkManager(networkManager)
{

}

net::BoostNetworkClient::~BoostNetworkClient()
{

}

ip::tcp::socket &net::BoostNetworkClient::getSocket()
{
    return this->m_socket;
}

void net::BoostNetworkClient::bindRead()
{
    if (this->m_connected == false)
        this->m_connected = true;
    auto binding = boost::bind(&BoostNetworkClient::readHandler, shared_from_this(), placeholders::error, placeholders::bytes_transferred);
    async_read_until(this->m_socket, this->m_buffer, "\0", binding);
}

void net::BoostNetworkClient::readHandler(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (error) {
        disconnect(error.message());
        return;
    }
    auto ptr = static_cast<const char *>(m_buffer.data().data());
    auto size = m_buffer.data().size();
    std::string message(ptr, size);
    this->m_buffer.consume(size);
    this->m_networkManager.recvData(shared_from_this(), message);
    bindRead();
}

void net::BoostNetworkClient::writeHandler(const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (error)
        disconnect(error.message());
}

bool net::BoostNetworkClient::send(const std::string &data)
{
    auto binding = boost::bind(&BoostNetworkClient::writeHandler, shared_from_this(), placeholders::error, placeholders::bytes_transferred);
    this->m_socket.async_write_some(buffer(data, data.size()), binding);
    return true;
}

void net::BoostNetworkClient::disconnect(const std::string &message)
{
    this->m_networkManager.removeClient(shared_from_this());
    this->m_socket.close();
    this->m_connected = false;
}

std::size_t net::BoostNetworkClient::getId() const noexcept
{
    return (std::size_t)this;
}
