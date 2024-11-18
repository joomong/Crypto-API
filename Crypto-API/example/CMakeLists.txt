cmake_minimum_required(VERSION 3.22)
project(example)

set(CMAKE_CXX_STANDARD 11)

add_executable(example
        ../src/jsoncpp.cpp
        ws.cpp)

# Link external libraries
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_library(WEBSOCKETS_LIBRARY websockets REQUIRED)

target_link_libraries(example
    ${WEBSOCKETS_LIBRARY}
    OpenSSL::SSL
    CURL::libcurl
)

# Include directories
target_include_directories(example PUBLIC 
    ../src
    /usr/include/
    /usr/include/curl
    /usr/include/openssl)

