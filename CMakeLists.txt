cmake_minimum_required(VERSION 3.16)
project(tor-echo-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Require Boost.System (Asio is header-only in Boost distributions)
find_package(Boost 1.88 REQUIRED COMPONENTS system)

add_executable(tor-echo-client
    src/main.cpp
    src/TorInstance.cpp
    src/Socks5Client.cpp
    src/TorStream.cpp
)

target_include_directories(tor-echo-client PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(tor-echo-client PRIVATE Boost::system)

