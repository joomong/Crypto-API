cmake_minimum_required(VERSION 3.16.3)
project(example)

set(CMAKE_CXX_STANDARD 11)

# Build type 설정: 디버그 모드 포함
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug) # 기본 빌드 타입을 Debug로 설정
endif()

# 디버그 플래그 추가
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Add executable
add_executable(example
        ../src/jsoncpp.cpp
        ws-example.cpp)

# Link external libraries
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_library(WEBSOCKETS_LIBRARY websockets REQUIRED)

# Find the cryptoapi library with debug symbols
find_library(CRYPTOAPI_LIBRARY
    NAMES cryptoapi
    HINTS "${CMAKE_SOURCE_DIR}/../lib"
)
if(NOT CRYPTOAPI_LIBRARY)
    message(FATAL_ERROR "Could not find libcryptoapi.so in ${CMAKE_SOURCE_DIR}/../lib")
endif()

# Link the libraries
target_link_libraries(example
    ${WEBSOCKETS_LIBRARY}
    OpenSSL::SSL
    CURL::libcurl
    ${CRYPTOAPI_LIBRARY}  # 전체 경로로 링크
)

# Include directories
target_include_directories(example PUBLIC 
    ../src
    /usr/include/
    /usr/include/curl
    /usr/include/openssl)
