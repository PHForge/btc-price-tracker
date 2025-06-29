/*
 * Bitcoin Price Fetcher
 * Fetches Bitcoin price from CoinGecko API and displays it in the console.
 * Uses httplib for HTTP requests, nlohmann::json for JSON parsing.
 *
 * Dev with passion by: PHForge
 * License: MIT License
 * Version: 0.0.7
 */

#include <httplib.h> // For HTTP requests
#include <json.hpp> // For JSON manipulation
#include <iostream> // For console output
#include <string> // For string manipulation
#include <thread> // For sleep functionality  
#include <chrono> // For time manipulation
#include <iomanip> // For formatted output

#ifdef _WIN32 // For Windows-specific functionality
#include <windows.h> // For UTF-8 encoding
#endif

// Define ANSI color codes for console output
const std::string COLOR_LIGHT_BLUE = "\033[1;34m";
const std::string COLOR_GREEN = "\033[1;32m";
const std::string COLOR_CYAN = "\033[1;36m";
const std::string COLOR_RED = "\033[1;31m";
const std::string COLOR_YELLOW = "\033[1;33m";
const std::string COLOR_RESET = "\033[0m"; // Reset color 
const std::string CLEAR_SCREEN = "\033[2J\033[H"; // Clear screen and move cursor to home position

// Define the JSON namespace for convenience
using json = nlohmann::json;

// Function to enable ANSI escape codes for colored output on Windows
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
    auto now = std::chrono::system_clock::now(); // Get current time
    auto time = std::chrono::system_clock::to_time_t(now); // Convert to time_t
    std::ostringstream oss; // Create an output string stream
    oss << std::put_time(std::localtime(&time), "%m/%d/%Y %I:%M %p"); // Format the time
    return oss.str();
}

// Function to fetch the current Bitcoin price from CoinGecko API
double getBitcoinPrice() {
    try {
        static httplib::Client cli("https://api.coingecko.com"); // Create a client for CoinGecko API
        static bool initialized = false; // Static variable to ensure initialization only once
        // Initialize connection and read timeouts only once
        // This prevents repeated initialization on each function call
        if (!initialized) { 
            cli.set_connection_timeout(5);
            cli.set_read_timeout(5);
            initialized = true;
        }
        // Attempt to fetch the Bitcoin price with retries
        // This loop will retry up to 3 times in case of connection issues or errors
        const int maxRetries = 3; // Maximum number of retries
        for (int attempt = 1; attempt <= maxRetries; ++attempt) {
            auto res = cli.Get("/api/v3/simple/price?ids=bitcoin&vs_currencies=usd"); 
            // Check if the response is null (indicating a connection failure)
            if (!res) {
                std::cerr << COLOR_RED << "Error: Failed to connect to CoinGecko API (Attempt " << attempt << "/" << maxRetries << ")" << COLOR_RESET << std::endl;
                if (attempt < maxRetries) {
                    std::cerr << COLOR_YELLOW << "Retrying in 5 seconds..." << COLOR_RESET << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(5));
                    continue;
                }
                return -1.0;
            }
            // Check if the response status is not OK (200)
            if (res->status != 200) {
                std::cerr << COLOR_RED << "HTTP error: Status code " << res->status << " (Attempt " << attempt << "/" << maxRetries << ")";
                if (res->status == 429) {
                    std::cerr << " (Rate limit exceeded)";
                    if (attempt < maxRetries) {
                        std::cerr << COLOR_YELLOW << "Retrying in 10 seconds..." << COLOR_RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(10));
                        continue;
                    }
                // Handle specific HTTP status codes
                } else if (res->status == 400) {
                    std::cerr << " (Bad request)";
                } else if (res->status == 401) {
                    std::cerr << " (Unauthorized access)";
                } else if (res->status == 404) { 
                    std::cerr << " (Resource not found)";
                } else if (res->status >= 500) {
                    std::cerr << " (Server error)";
                    if (attempt < maxRetries) {
                        std::cerr << COLOR_YELLOW << "Retrying in 5 seconds..." << COLOR_RESET << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(5));
                        continue;
                    }
                }
                // If we reach here, it means the request failed after all retries
                std::cerr << COLOR_RESET << std::endl;
                return -1.0;
            }
            // Success: parse JSON and return price
            json j = json::parse(res->body);
            if (!j.contains("bitcoin") || !j["bitcoin"].contains("usd")) {
                std::cerr << COLOR_RED << "Error: Invalid JSON structure (missing 'bitcoin' or 'usd' key)" << COLOR_RESET << std::endl;
                return -1.0;
            }
            return j["bitcoin"]["usd"].get<double>(); // Extract the Bitcoin price in USD
        }
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << COLOR_RED << "Error: Failed to parse JSON response: " << e.what() << COLOR_RESET << std::endl;
        return -1.0;
    }
    catch (const std::exception& e) {
        std::cerr << COLOR_RED << "Unexpected error: " << e.what() << COLOR_RESET << std::endl;
        return -1.0;
    }
    return -1.0; // Fallback in case of unexpected loop exit
}

// Function to display a decorative border
// The width of the border can be specified, default is 50 characters
void printBorder(const std::string& title, int width = 50) {
    std::cout << COLOR_LIGHT_BLUE; // Light blue for the border
    std::cout << std::string(width, '=') << "\n";
    std::cout << std::string((width - title.length() - 2) / 2, ' ') << " " << title << " " << std::string((width - title.length() - 2) / 2, ' ') << "\n";
    std::cout << std::string(width, '=') << COLOR_RESET << "\n";
}

// Function to print a formatted line with label, value, and color
void printFormattedLine(const std::string& label, const std::string& value, const std::string& color) {
    std::cout << color << std::setw(25) << std::left << label << value << COLOR_RESET << "\n";
}

int main() {
        // Set console to UTF-8 encoding on Windows
        #ifdef _WIN32
            SetConsoleOutputCP(CP_UTF8);
        #endif

        // Enable ANSI escape codes for colored output
        enableANSICodes();

        while (true) {
        
        // Clear the console for a fresh display, using flush to ensure it works immediately
        std::cout << CLEAR_SCREEN << std::flush;

        // Print the title and border
        printBorder("Bitcoin Price Tracker");
        
        // Print the current time
        double price = getBitcoinPrice();
        if (price >= 0.0) { // Check if the price is valid
            std::ostringstream oss; // Create an output string stream for formatted output
            oss << "$" << std::fixed << std::setprecision(2) << price; // Format the price to 2 decimal places
            printFormattedLine("Bitcoin Price:", oss.str(), COLOR_GREEN); // Print the price in green
        } else {
            printFormattedLine("Status:", "Unable to retrieve price.", COLOR_RED); // Print error message in red
        }
        printFormattedLine("Last Updated:", getCurrentTimeFormatted(), COLOR_CYAN); // Print the last updated time in cyan

        printBorder("", 50); // Print a decorative border at the bottom

        // Message indicating the next update and my signature
        std::cout << COLOR_YELLOW << "Next update in 60 seconds..." << COLOR_RESET << "\n";
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "                        Thanks for using this tool\n";
        std::cout << "                                        By " << COLOR_LIGHT_BLUE << "PHForge" << COLOR_RESET << "\n";
        
        // Sleep for 60 seconds before the next update
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    return 0;
}