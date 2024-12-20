cmake_minimum_required(VERSION 3.16)
project(Crypto_API)

set(CMAKE_CXX_STANDARD 11)

# Set the output directory for the libraries
set(LIBRARY_OUTPUT_PATH ../lib)

# Optimization for GCC
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# Add the Crypto_API library
add_library(cryptoapi SHARED 
    src/binance.cpp
    src/hashkey.cpp
    src/exchange.cpp
    src/jsoncpp.cpp 
    src/binanceusdm.cpp
)

# Link external libraries
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_library(WEBSOCKETS_LIBRARY websockets REQUIRED)

target_link_libraries(cryptoapi 
    ${WEBSOCKETS_LIBRARY}
    OpenSSL::SSL
    CURL::libcurl
)

# Include directories
target_include_directories(cryptoapi PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/json
    /usr/include/
    /usr/include/curl
    /usr/include/openssl)