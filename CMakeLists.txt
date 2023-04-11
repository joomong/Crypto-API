cmake_minimum_required(VERSION 3.25)
project(Crypto_API)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Crypto_API
        binance.cpp
        binance.h)
