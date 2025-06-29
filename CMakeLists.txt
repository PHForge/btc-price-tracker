# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.15)

# Define the project with version and language
project(BTC_Price_Tracker VERSION 0.0.8 LANGUAGES CXX)

# Set C++20 standard and ensure it's required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable for the project
add_executable(btc-price-tracker src/main.cpp)

# Include directories for header-only libraries (cpp-httplib, nlohmann/json)
target_include_directories(btc-price-tracker PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Enable OpenSSL support for cpp-httplib
add_definitions(-DCPPHTTPLIB_OPENSSL_SUPPORT)

# Find and link OpenSSL libraries
find_package(OpenSSL REQUIRED)
if (OpenSSL_FOUND)
    target_include_directories(btc-price-tracker PRIVATE ${OPENSSL_INCLUDE_DIR})
    target_link_libraries(btc-price-tracker PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

# Link platform-specific libraries for Windows
if (WIN32)
    target_link_libraries(btc-price-tracker PRIVATE ws2_32 crypt32)
endif()