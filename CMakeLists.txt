cmake_minimum_required(VERSION 3.25)
project(Crypto_API)

set(brew /opt/homebrew/opt)
set(CMAKE_CXX_STANDARD 14)

include_directories(Crypto_API rest/include
        ${brew}/curl/include
        ${brew}/openssl@1.1/include)

add_executable(Crypto_API
        rest/src/binance.cpp
        rest/src/exchange.cpp
        rest/test/test-binance.cpp)

# Add library directories
target_link_libraries(Crypto_API
        ${brew}/curl/lib/libcurl.dylib
        ${brew}/openssl@1.1/lib/libssl.dylib)

