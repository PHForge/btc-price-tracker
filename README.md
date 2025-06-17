# Bitcoin Price Tracker 🔎

A real-time Bitcoin (BTC) price tracker written in **C++20**, fetching live USD prices from the CoinGecko API via HTTPS. This project uses modern C++ programming, HTTP client integration, JSON parsing, and cross-platform build configuration using CMake.

![Language](https://img.shields.io/badge/language-C++-blue.svg) ![License](https://img.shields.io/badge/license-MIT-darkblue.svg) ![SoftVersion](https://img.shields.io/badge/SoftVersion-0.1-black)

*Example output: `Bitcoin price: $106000.00 - 06/16/2025 at 2:13 p.m.`*

<br>

## Features 📋
- Fetches Bitcoin price in USD from CoinGecko API every 60 seconds.
- Displays price with timestamp in US format (MM/DD/YYYY at HH:MM a.m./p.m.).
- Handles HTTP errors and network exceptions gracefully.
- Clears console for clean, real-time updates.
- Supports UTF-8 encoding for proper character display.
- Cross-platform build system using CMake, compatible with Windows, Linux, and macOS.

<br>

## System Requirements ⚙️

The following components are required to build, run, or contribute to this project:

| Component          | Requirement                              | Notes                                      |
|--------------------|------------------------------------------|--------------------------------------------|
| **Language**       | C++20                                    | Core language used for the project         |
| **Compiler**       | GCC (via MSYS2 UCRT64)                   | Ensure G++ is installed; other compilers like Clang or MSVC may work with CMake |
| **Libraries**      | `cpp-httplib`, `nlohmann/json`, OpenSSL, WinSock (`ws2_32`), `crypt32` | Header-only libraries (`cpp-httplib`, `nlohmann/json`) included in `include/`; OpenSSL installed via MSYS2 |
| **Build System**   | CMake 3.15 or higher                     | Used for cross-platform build configuration |
| **IDE/Editor**     | VS Code (recommended) or any C++-compatible IDE/terminal | Configured with `tasks.json` and `launch.json` for compilation and debugging |
| **Debugger**       | GDB (via MSYS2 UCRT64)                   | For debugging in VS Code                   |
| **Version Control**| Git                                      | Required to clone the repository           |
| **OS**             | Windows (tested with MSYS2 UCRT64); Linux/macOS (with adjustments) | CMake ensures cross-platform compatibility |

> [!TIP]
> For an optimal setup on Windows, install [MSYS2 UCRT64](https://www.msys2.org/) and use the following command to install dependencies:
> ```bash
> pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-openssl mingw-w64-ucrt-x86_64-gdb
> ```
> On Linux/macOS, use package managers like `apt` or `brew` to install `g++`, `cmake`, `openssl`, and `git`.

<br>

## Installation </>

1. **Clone the Repository**:
	```bash
	git clone https://github.com/your-username/btc-price-tracker.git
    cd btc-price-tracker
	```

2. **Install dependencies:**:
    - Windows (MSYS2 UCRT64):
		```bash
		pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-openssl mingw-w64-ucrt-x86_64-gdb
		```
	- Linux (Ubuntu/Debian):
		```bash
		sudo apt update
        sudo apt install g++ cmake libssl-dev git
		```

3. **Build with CMake:**:
	```bash
	mkdir build && cd build
	```
	- Windows: `cmake -G "MinGW Makefiles" ..`
	- Linux: `cmake ..`

4. **Build the project:**:
	```bash
	cmake --build .
	```

5. **Run the executable:**:
	- Windows: `./btc-price-tracker.exe`
	- Linux: `./btc-price-tracker`

<br>

## Project Structure 🗂️
```bash
btc-price-tracker/
├── include/                    // Header files for external libraries
│   ├── httplib.h               // HTTP client library (cpp-httplib): https://github.com/yhirose/cpp-httplib
│   ├── json.hpp                // JSON parsing library (nlohmann/json): https://github.com/nlohmann/json
├── src/                        // Source code
│   ├── main.cpp                // Main application (fetches and displays Bitcoin price)
├── LICENSE                     // MIT License file
├── CMakeLists.txt              // CMake build configuration for cross-platform builds
└── README.md                   // Project documentation
```

<br>

## License 🧾

This project is licensed under the **MIT License** - see the LICENSE file for details.

<br>

## Crédits ☕

> Developed by PHForge. 
> Feel free to reach out via [GitHub](https://github.com/PHForge) for feedback or collaboration ideas!

> Special thanks ❤️ to my wife and son for their patience and love.

