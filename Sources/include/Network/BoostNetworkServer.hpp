/**
 * @file BoostNetworkServer.hpp
 * @author Gabriel Hamel (gabriel.hamel@epitech.eu)
 * @brief Boost encapsulation of the server tcp
 * @version 1.0
 * @date 2020-01-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include <boost/asio.hpp>
#include "INetworkServer.hpp"
#include "NetworkManager.hpp"
#include "BoostNetworkClient.hpp"
#include "NetworkManager.hpp"

namespace net
{

    class BoostNetworkServer : public net::INetworkServer
    {
        private:
            boost::asio::io_service m_io;
            boost::asio::ip::tcp::socket m_socket;
            boost::asio::ip::tcp::acceptor m_acceptor;
            net::NetworkManager m_networkManager;
            void bindAcceptor();
            void acceptHandler(boost::shared_ptr<net::BoostNetworkClient> connection, const boost::system::error_code &error);
        public:
            BoostNetworkServer(unsigned short port);
            ~BoostNetworkServer();
            void run();
            void stop();
    };

}
