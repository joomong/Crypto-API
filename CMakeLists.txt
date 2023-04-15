cmake_minimum_required(VERSION 3.25)
project(Crypto_API)

set(brew /opt/homebrew/opt)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(crypto-cpp)

include_directories(Crypto_API
        crypto-cpp/include
        ${brew}/curl/include
        ${brew}/openssl@1.1/include)

add_library(Crypto_API STATIC
        crypto-cpp/src/binance.cpp
        crypto-cpp/src/exchange.cpp
        test/test-binance.cpp
        crypto-cpp/include/binance.h
        crypto-cpp/include/exchange.h
        crypto-cpp/include/json)


# Add library directories
target_link_libraries(Crypto_API
        ${brew}/curl/lib/libcurl.dylib
        ${brew}/openssl@1.1/lib/libssl.dylib)

