cmake_minimum_required(VERSION 3.16)
project(tor-echo-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost
find_package(Boost 1.88 REQUIRED COMPONENTS system)

# Set Homebrew readline prefixes (ARM & Intel)
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH
        /opt/homebrew/opt/readline
        /usr/local/opt/readline
    )
endif()

# Try to find Readline
find_path(READLINE_INCLUDE_DIR readline/readline.h)
find_library(READLINE_LIB readline)
find_library(HISTORY_LIB history)

if (READLINE_INCLUDE_DIR AND READLINE_LIB AND HISTORY_LIB)
    message(STATUS "Found Readline: ${READLINE_LIB}")
    add_compile_definitions(HAVE_READLINE)
    set(READLINE_FOUND TRUE)
else()
    message(STATUS "Readline not found — falling back to std::getline")
    set(READLINE_FOUND FALSE)
endif()

add_executable(tor-echo-client
    src/main.cpp
    src/TorInstance.cpp
    src/TorStream.cpp
    src/Socks5Client.cpp
)

target_include_directories(tor-echo-client PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${READLINE_INCLUDE_DIR}
)

target_link_libraries(tor-echo-client PRIVATE
    ${Boost_LIBRARIES}
)

if (READLINE_FOUND)
    target_link_libraries(tor-echo-client PRIVATE
        ${READLINE_LIB}
        ${HISTORY_LIB}
    )
endif()

