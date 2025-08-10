#include "TorInstance.hpp"
#include <iostream>

TorInstance::TorInstance(std::string socks_host, unsigned short socks_port) noexcept
    : socks_host_(std::move(socks_host)), socks_port_(socks_port) {}

TorInstance::~TorInstance() { stop(); }

void TorInstance::start() {
    std::cout << "[TorInstance] Using SOCKS proxy " << socks_host_
              << ":" << socks_port_ << " (assumes Tor daemon is running)\n";
}

void TorInstance::stop() {
    std::cout << "[TorInstance] Stopping (no action performed)\n";
}

