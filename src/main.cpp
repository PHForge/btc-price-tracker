#include <httplib.h> // For HTTP requests
#include <json.hpp> // For JSON manipulation
#include <iostream>
#include <string>
#include <thread>
#include <chrono> // For time operations
#include <iomanip> // For formatting date/time

#ifdef _WIN32
#include <windows.h> // For UTF-8 encoding
#endif

using json = nlohmann::json;

// Function to get the current formatted time
std::string getCurrentTimeFormatted() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%m/%d/%Y at %I:%M %p");
    return oss.str();
}

double getBitcoinPrice() {
    try {
        // Create an HTTP client to connect to the CoinGecko API
        httplib::Client cli("https://api.coingecko.com");
        auto res = cli.Get("/api/v3/simple/price?ids=bitcoin&vs_currencies=usd");
        
        if (!res || res->status != 200) {
            std::cerr << "Erreur HTTP : " << (res ? res->status : -1) << std::endl;
            return -1.0;
        }
        // Parse the JSON response
        json j = json::parse(res->body);
        return j["bitcoin"]["usd"].get<double>();
    }
    // Handle exceptions and errors
    catch (const std::exception& e) {
        std::cerr << "Exception : " << e.what() << std::endl;
        return -1.0;
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Force UTF-8 encoding for Windows console
#endif
    while (true) {
#ifdef _WIN32
        system("cls"); // Clear console on Windows
#else
        system("clear"); // Clear console on Linux/Mac
#endif
        // Get the current Bitcoin price and print it with the formatted time
        double price = getBitcoinPrice();
        if (price >= 0.0) {
            std::cout << "Bitcoin price: $" << std::fixed << std::setprecision(2) << price 
                      << " - " << getCurrentTimeFormatted() << std::endl;
        }
        else {
            std::cout << "Unable to retrieve price." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(60)); // Wait 60 seconds before next request
    }
    return 0;
}