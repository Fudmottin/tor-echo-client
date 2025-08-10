#pragma once
#include <boost/asio.hpp>
#include <string>
#include "Socks5Client.hpp"

class TorStream {
public:
    TorStream(boost::asio::io_context& ioc,
              std::string socks_host,
              unsigned short socks_port,
              std::string onion_host,
              unsigned short onion_port);

    // Connect the SOCKS proxy to the onion destination (throws on error)
    void connect();

    // write and read (throws on error)
    void send_line(const std::string& line);
    std::string receive_some(std::size_t max_bytes = 4096);

private:
    boost::asio::io_context& ioc_;
    Socks5Client client_;
    std::string onion_host_;
    unsigned short onion_port_;
};

