#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "INetworkClient.hpp"
#include "NetworkManager.hpp"

namespace zia::net
{

    class BoostNetworkClient : public zia::net::INetworkClient, public boost::enable_shared_from_this<zia::net::BoostNetworkClient>
    {
        private:
            boost::asio::ip::tcp::socket m_socket;
            bool m_connected;
            boost::asio::streambuf m_buffer;
            zia::net::NetworkManager &m_networkManager;
        public:
            BoostNetworkClient(boost::asio::basic_socket_acceptor<boost::asio::ip::tcp> &ec, NetworkManager &networkManager);
            ~BoostNetworkClient();
            void send(const std::string &data);
            boost::asio::ip::tcp::socket &getSocket();
            void bindRead();
            std::size_t getId() const;
            void disconnect(const std::string &message);
            void readHandler(const boost::system::error_code &error, std::size_t bytes_transferred);
            void writeHandler(const boost::system::error_code &error, std::size_t bytes_transferred);
    };

}
