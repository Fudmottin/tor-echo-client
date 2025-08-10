// src/main.cpp
#include "TorInstance.hpp"
#include "TorStream.hpp"

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <optional>
#include <string>

#ifdef HAVE_READLINE
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

static std::optional<std::string> get_input(const char* prompt) {
#ifdef HAVE_READLINE
    char* buf = readline(prompt);
    if (!buf)                // EOF (Ctrl-D)
        return std::nullopt;
    std::string s(buf);
    free(buf);
    if (!s.empty()) add_history(s.c_str());
    return s;
#else
    std::cout << prompt << std::flush;
    std::string s;
    if (!std::getline(std::cin, s)) // EOF
        return std::nullopt;
    return s;
#endif
}

int main() try {
    const std::string onion =
        "nb5iaajanzfty33y2tkuengk37gbjjeylr5gtwnkhkxkrls6k33gvkad.onion";
    const unsigned short onion_port = 2000; // correct type

    TorInstance tor; // default 127.0.0.1:9050
    tor.start();

    boost::asio::io_context ioc;

    // Note: constructor expects unsigned short for ports
    TorStream stream(ioc, tor.socks_host(), tor.socks_port(), onion, onion_port);

    std::cout << "[main] Establishing circuit and connecting to onion...\n";
    stream.connect();
    std::cout << "[main] Connected. Type text and press Enter to send. Type 'quit' to exit.\n";

    while (true) {
        auto maybe = get_input("tor-echo> ");
        if (!maybe) { // EOF
            std::cout << "\n[main] EOF, exiting.\n";
            break;
        }
        const std::string line = *maybe;
        if (line == "quit") break;
        if (line.empty()) continue; // ignore blank lines

        const auto t0 = std::chrono::steady_clock::now();
        stream.send_line(line);
        const std::string reply = stream.receive_some();
        const auto t1 = std::chrono::steady_clock::now();

        std::chrono::duration<double> rtt = t1 - t0;
        std::cout << "Echo: " << reply << " (" << rtt.count() << " s)\n";
    }

    tor.stop();
    return 0;
}
catch (const std::exception& e) {
    std::cerr << "[ERROR] " << e.what() << '\n';
    return 2;
}

