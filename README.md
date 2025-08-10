# tor-echo-client

A simple command line client that uses Tor to connect to a Tor hidden service echo server.

---

## Purpose

This program is a personal learning project to understand how to use the Tor network and its SOCKS5 proxy interface via C++.  
It is **not intended for production or practical use**. The focus is on building a minimal client that:  
- Establishes a Tor circuit through a local Tor daemon  
- Connects to a hard-coded onion address running an echo service  
- Sends user input and displays the echoed response with round-trip timing  
- Provides a command prompt with line editing and history support (using `readline` on Unix-like systems)  

---

## Usage

1. Ensure the Tor daemon is installed and running on your machine (default SOCKS5 port 9050).  
2. Build the project with CMake and your compiler of choice.  
3. Run the executable and interact with the echo server via the prompt.  
4. Type `quit` or press Ctrl-D to exit.

---

## Dependencies

- C++20 compiler (Apple Clang, GCC, or MSVC)  
- Boost.System (for networking abstractions)  
- Readline (optional, for better prompt experience on macOS, Linux, and *BSD)  
- A running Tor daemon on localhost (default SOCKS5 port 9050)

---

## License

MIT License — see [LICENSE](LICENSE)

