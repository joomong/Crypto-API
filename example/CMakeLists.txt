cmake_minimum_required(VERSION 3.25)
project(Crypto_API)

set(CMAKE_CXX_STANDARD 14)
set(brew /opt/homebrew/opt)

# Example build settings for crypto API
include_directories(
        ../include
        ../src/json
        ${brew}/curl/include
        ${brew}/openssl@1.1/include)

add_executable(binance-example
        binance_example.cpp
#        ../src/exchange.cpp
        ../src/jsoncpp.cpp)

target_link_libraries(binance-example
        ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-build-debug/lib/libcryptoapi.a
        ${brew}/curl/lib/libcurl.dylib
        ${brew}/openssl@1.1/lib/libcrypto.dylib)