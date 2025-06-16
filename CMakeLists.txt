cmake_minimum_required(VERSION 3.15)
project(BTC_Price_Tracker LANGUAGES CXX)

# Define the C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the executable
add_executable(btc-price-tracker src/main.cpp)

# Enable OpenSSL support for cpp-httplib
add_definitions(-DCPPHTTPLIB_OPENSSL_SUPPORT)

# Find OpenSSL
find_package(OpenSSL REQUIRED)
if (OpenSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(btc-price-tracker PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

# Link Windows libraries
if (WIN32)
    target_link_libraries(btc-price-tracker PRIVATE ws2_32 crypt32)
endif()