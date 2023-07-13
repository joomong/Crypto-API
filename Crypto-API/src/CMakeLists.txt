cmake_minimum_required(VERSION 3.22)
project(Crypto_API)

set(CMAKE_CXX_STANDARD 11)

# set the output directory for the libraries
set(LIBRARY_OUTPUT_PATH ../lib)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# Crypto_API library
add_library(cryptoapi SHARED 
binance.cpp
exchange.cpp
jsoncpp.cpp 
binanceusdm.cpp)

link_directories(
        /usr/lib/x86_64-linux-gnu/libcurl.so
        /usr/lib/x86_64-linux-gnu/libcrypto.so
        /usr/lib/x86_64-linux-gnu/libwebsockets.so)
        
        target_link_libraries(cryptoapi
        /usr/lib/x86_64-linux-gnu/libwebsockets.so
        /usr/lib/x86_64-linux-gnu/libcurl.so
        /usr/lib/x86_64-linux-gnu/libcrypto.so)
        
        
        target_include_directories(cryptoapi PUBLIC 
        /usr/include/
        /usr/include/curl
        /usr/include/openssl)
        
        include_directories(
                /usr/include/
                /usr/include/curl
                /usr/include/openssl)
                