cmake_minimum_required(VERSION 3.16)
project(Crypto_API)

set(CMAKE_CXX_STANDARD 20)

# Set the output directory for the libraries to be outside the build directory
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# Build type 설정: 디버그 모드 포함
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug) # 기본 빌드 타입을 Debug로 설정
endif()

# 추가 플래그: 디버그 심볼 추가
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Optimization for GCC (Debug 모드일 때 최적화 플래그 제거)
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

# Add the Crypto_API library
add_library(cryptoapi SHARED 
    src/Hashkey.cpp
    src/OKX.cpp
    src/HttpClient.cpp
    src/Utils.cpp
    src/jsoncpp.cpp 
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
