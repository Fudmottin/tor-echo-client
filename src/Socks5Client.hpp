#pragma once
#include <boost/asio.hpp>
#include <string>

class Socks5Client {
public:
    Socks5Client(boost::asio::io_context& ioc,
                 std::string socks_host,
                 unsigned short socks_port);

    // Establish TCP connection to SOCKS proxy and perform SOCKS5 connect
    // to dest_host:dest_port (domain name). Throws on failure.
    void connect_to_destination(const std::string& dest_host, unsigned short dest_port);

    // Write and read convenience methods (throw on error)
    std::size_t write_some(const std::string& data);
    std::string read_some(std::size_t max_bytes = 4096);

private:
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::socket socket_;
    std::string socks_host_;
    unsigned short socks_port_;
};

