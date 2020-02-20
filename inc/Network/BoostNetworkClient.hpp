/**
 * @file BoostNetworkClient.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief An boost asio instance to store and comunicate with a network client
 * @version 1.0
 * @date 2020-01-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "IClient.hpp"
#include "NetworkManager.hpp"

using namespace boost::asio;

namespace net
{

    class BoostNetworkClient : public net::IClient, public boost::enable_shared_from_this<net::BoostNetworkClient>
    {
        private:
            ip::tcp::socket m_socket;
            bool m_connected;
            std::unique_ptr<streambuf> m_buffer;
            net::NetworkManager &m_networkManager;
        public:
            BoostNetworkClient(basic_socket_acceptor<ip::tcp> &ec, NetworkManager &networkManager);
            ~BoostNetworkClient();
            bool send(const std::string &data);
            ip::tcp::socket &getSocket();
            void bindRead();
            void disconnect(const std::string &message);
            void readHandler(const boost::system::error_code &error, std::size_t bytes_transferred);
            void writeHandler(const boost::system::error_code &error, std::size_t bytes_transferred);
            std::size_t getId() const noexcept;
    };

}
