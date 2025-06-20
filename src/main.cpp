/*
 * Bitcoin Price Fetcher
 * Fetches Bitcoin price from CoinGecko API and displays it in the console.
 * Uses httplib for HTTP requests, nlohmann::json for JSON parsing.
 *
 * Dev with passion by: PHForge
 * License: MIT License
 * Version: 0.0.2
 */

#include <httplib.h> // For HTTP requests
#include <json.hpp> // For JSON manipulation
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <iomanip>

#ifdef _WIN32
#include <windows.h> // For UTF-8 encoding
#endif

using json = nlohmann::json;

// Function to enable ANSI escape codes for colored output on Windows
// This is necessary for colored output in the console.
void enableANSICodes() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(hConsole, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, consoleMode);
#endif
}

// Function to get the current formatted time
// Returns a string with the current time formatted as "MM/DD/YYYY HH:MM AM/PM"
std::string getCurrentTimeFormatted() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%m/%d/%Y %I:%M %p");
    return oss.str();
}

// Function to fetch the current Bitcoin price from CoinGecko API
// Returns the price in USD as a double, or -1.0 if an error occurs
double getBitcoinPrice() {
    try {
        httplib::Client cli("https://api.coingecko.com");
        auto res = cli.Get("/api/v3/simple/price?ids=bitcoin&vs_currencies=usd");
        if (!res || res->status != 200) {
            std::cerr << "Erreur HTTP : " << (res ? res->status : -1) << std::endl;
            return -1.0;
        }
        json j = json::parse(res->body);
        return j["bitcoin"]["usd"].get<double>();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception : " << e.what() << std::endl;
        return -1.0;
    }
}

// Function to display a decorative border
// The width of the border can be specified, default is 50 characters
void printBorder(const std::string& title, int width = 50) {
    std::cout << "\033[1;34m"; // Light blue for the border
    std::cout << std::string(width, '=') << "\n";
    std::cout << std::string((width - title.length() - 2) / 2, ' ') 
              << " " << title << " " 
              << std::string((width - title.length() - 2) / 2, ' ') << "\n";
    std::cout << std::string(width, '=') << "\033[0m\n";
}

int main() {

    // MODIFICATION: Set console output to UTF-8 encoding on Windows
    // This allows for proper display of special characters in the console.
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    // Function to enable ANSI escape codes for colored output on Windows
    // This is necessary for colored output in the console.
    enableANSICodes();

    while (true) {
        // clear the console for a fresh display
        // This is done to avoid cluttering the console with previous outputs.
        #ifdef _WIN32
                system("cls");
        #else
                system("clear");
        #endif

        // Print the title with a decorative border
        printBorder("Bitcoin Price Tracker");
        
        // Fetch the Bitcoin price and display it
        // If the price is successfully retrieved, it will be displayed in green.
        double price = getBitcoinPrice();
        if (price >= 0.0) {
            std::cout << "\033[1;32m"; // Green for the price
            std::cout << std::setw(25) << std::left << "Bitcoin Price:" 
                      << "$" << std::fixed << std::setprecision(2) << price << "\n";
            std::cout << "\033[1;36m"; // Cyan for the time
            std::cout << std::setw(25) << std::left << "Last Updated:" 
                      << getCurrentTimeFormatted() << "\033[0m\n";
        } else {
            std::cout << "\033[1;31m"; // Red for the error
            std::cout << std::setw(25) << std::left << "Status:" 
                      << "Unable to retrieve price." << "\n";
            std::cout << "\033[1;36m";
            std::cout << std::setw(25) << std::left << "Last Updated:" 
                      << getCurrentTimeFormatted() << "\033[0m\n";
        }

        // Lower border
        printBorder("", 50);

        // Message indicating the next update
        std::cout << "\033[1;33m"; // Yellow for the message
        std::cout << "Next update in 60 seconds...\033[0m\n";
        
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    return 0;
}