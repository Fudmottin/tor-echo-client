#include "TorStream.hpp"
#include <iostream>

TorStream::TorStream(boost::asio::io_context& ioc,
                     std::string socks_host,
                     unsigned short socks_port,
                     std::string onion_host,
                     unsigned short onion_port)
    : ioc_(ioc),
      client_(ioc_, std::move(socks_host), socks_port),
      onion_host_(std::move(onion_host)),
      onion_port_(onion_port)
{}

void TorStream::connect() {
    std::cout << "[TorStream] Asking SOCKS proxy to connect to onion service "
              << onion_host_ << ":" << onion_port_ << "\n";
    client_.connect_to_destination(onion_host_, onion_port_);
}

void TorStream::send_line(const std::string& line) {
    // send line + newline
    client_.write_some(line + "\n");
}

std::string TorStream::receive_some(std::size_t max_bytes) {
    return client_.read_some(max_bytes);
}

