/*
 * Bitcoin Price Fetcher
 * Fetches Bitcoin price from CoinGecko API and displays it in the console.
 * Uses httplib for HTTP requests, nlohmann::json for JSON parsing.
 *
 * Dev with passion by: PHForge
 * License: MIT License
 * Version: 0.0.1
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

// MODIFICATION: Fonction pour activer les codes ANSI sur Windows
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
std::string getCurrentTimeFormatted() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%m/%d/%Y %I:%M %p");
    return oss.str();
}

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

// MODIFICATION: Fonction pour afficher une bordure décorative
void printBorder(const std::string& title, int width = 50) {
    std::cout << "\033[1;34m"; // Bleu clair pour la bordure
    std::cout << std::string(width, '=') << "\n";
    std::cout << std::string((width - title.length() - 2) / 2, ' ') 
              << " " << title << " " 
              << std::string((width - title.length() - 2) / 2, ' ') << "\n";
    std::cout << std::string(width, '=') << "\033[0m\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    // MODIFICATION: Activation des codes ANSI pour les couleurs
    enableANSICodes();

    while (true) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        // MODIFICATION: Affichage stylisé avec bordures et couleurs
        printBorder("Bitcoin Price Tracker");
        
        double price = getBitcoinPrice();
        if (price >= 0.0) {
            std::cout << "\033[1;32m"; // Vert pour le prix
            std::cout << std::setw(25) << std::left << "Bitcoin Price:" 
                      << "$" << std::fixed << std::setprecision(2) << price << "\n";
            std::cout << "\033[1;36m"; // Cyan pour l'heure
            std::cout << std::setw(25) << std::left << "Last Updated:" 
                      << getCurrentTimeFormatted() << "\033[0m\n";
        } else {
            std::cout << "\033[1;31m"; // Rouge pour l'erreur
            std::cout << std::setw(25) << std::left << "Status:" 
                      << "Unable to retrieve price." << "\n";
            std::cout << "\033[1;36m";
            std::cout << std::setw(25) << std::left << "Last Updated:" 
                      << getCurrentTimeFormatted() << "\033[0m\n";
        }
        
        // MODIFICATION: Bordure inférieure
        printBorder("", 50);
        
        // MODIFICATION: Message indiquant la prochaine mise à jour
        std::cout << "\033[1;33m"; // Jaune pour le message
        std::cout << "Next update in 60 seconds...\033[0m\n";
        
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    return 0;
}