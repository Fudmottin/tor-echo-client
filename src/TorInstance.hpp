#pragma once
#include <string>

class TorInstance {
public:
    // socks_host and socks_port are where the Tor daemon is listening
    TorInstance(std::string socks_host = "127.0.0.1", unsigned short socks_port = 9050) noexcept;
    ~TorInstance();

    void start(); // logs what we will do
    void stop();  // logs and tidy up (no-op for now)

    std::string socks_host() const noexcept { return socks_host_; }
    unsigned short socks_port() const noexcept { return socks_port_; }

private:
    std::string socks_host_;
    unsigned short socks_port_;
};

