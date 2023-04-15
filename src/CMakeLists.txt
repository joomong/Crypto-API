cmake_minimum_required(VERSION 3.25)
project(Crypto_API)

set(brew /opt/homebrew/opt)
set(CMAKE_CXX_STANDARD 14)

# set the output directory for the libraries
set(LIBRARY_OUTPUT_PATH ../lib)

# Crypto_API library

add_library(cryptoapi STATIC
        binance.cpp
        exchange.cpp
        jsoncpp.cpp)

link_directories(
        ${brew}/libwebsockets/lib
        ${brew}/curl/lib
        ${brew}openssl@1.1/lib
)

target_link_libraries(cryptoapi
        ${brew}/curl/lib/libcurl.a
        ${brew}/openssl@1.1/lib/libcrypto.a
        ${brew}/libwebsockets/lib/libwebsockets.a)


target_include_directories(cryptoapi PUBLIC ../include
        ${brew}/libwebsockets/include
        ${brew}/curl/include
        ${brew}/openssl@1.1/include)

include_directories(
        ${brew}/libwebsockets/include
        ${brew}/curl/include
        ${brew}openssl@1.1/include)
