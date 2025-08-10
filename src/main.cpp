#include "TorInstance.hpp"
#include "TorStream.hpp"

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <string>

int main() {
    try {
        // Hard-coded .onion address from your service
        const std::string onion = "nb5iaajanzfty33y2tkuengk37gbjjeylr5gtwnkhkxkrls6k33gvkad.onion";
        const unsigned short onion_port = 2000;

        TorInstance tor; // default socks 127.0.0.1:9050
        tor.start();

        boost::asio::io_context ioc;

        TorStream ts(ioc, tor.socks_host(), tor.socks_port(), onion, onion_port);

        std::cout << "[main] Establishing circuit and connecting to onion...\n";
        ts.connect();
        std::cout << "[main] Connected. Type text and press Enter to send. Type 'quit' to exit.\n";

        std::string line;
        while (true) {
            std::cout << "tor-echo> " << std::flush;
            if (!std::getline(std::cin, line)) {
                std::cout << "\n[main] EOF, exiting.\n";
                break;
            }
            if (line == "quit") break;

            auto t0 = std::chrono::steady_clock::now();
            ts.send_line(line);
            auto reply = ts.receive_some();
            auto t1 = std::chrono::steady_clock::now();
            std::chrono::duration<double> rtt = t1 - t0;

            std::cout << "Echo: " << reply << " (" << rtt.count() << " s)\n";
        }

        tor.stop();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << "\n";
        return 2;
    }
}

