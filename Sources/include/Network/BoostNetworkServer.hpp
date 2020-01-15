#pragma once

#include <boost/asio.hpp>
#include "INetworkServer.hpp"
#include "NetworkManager.hpp"
#include "BoostNetworkClient.hpp"
#include "NetworkManager.hpp"

namespace zia::net
{

    class BoostNetworkServer : public zia::net::INetworkServer
    {
        private:
            boost::asio::io_service m_io;
            boost::asio::ip::tcp::socket m_socket;
            boost::asio::ip::tcp::acceptor m_acceptor;
            zia::net::NetworkManager m_networkManager;
            void bindAcceptor();
            void acceptHandler(boost::shared_ptr<zia::net::BoostNetworkClient> connection, const boost::system::error_code &error);
        public:
            BoostNetworkServer(unsigned short port);
            ~BoostNetworkServer();
            void run();
    };

}
