# Bitcoin Price Tracker 🔎

A real-time Bitcoin (BTC) price tracker, fetching live USD prices from the CoinGecko API via HTTPS. This project uses modern C++ programming, HTTP client integration, JSON parsing, and cross-platform build configuration using CMake.

![Language](https://img.shields.io/badge/language-C++-blue.svg) ![License](https://img.shields.io/badge/license-MIT-darkblue.svg) ![SoftVersion](https://img.shields.io/badge/SoftVersion-0.1-Green)

*Example output:*
```cpp
==================================================
              Bitcoin Price Tracker
==================================================
Bitcoin Price:           $108013.00
Last Updated:            07/05/2025 10:59 AM
==================================================

==================================================
Next update in 60 seconds...
[█-------------------] 6.7% (56s remaining)


          (press 'q' then Enter or Ctrl+C to exit)
                        Thanks for using this tool
                                        By PHForge
```

<br>

## Features 📋
- Fetches Bitcoin price in USD from CoinGecko API every 60 seconds.
- Displays price with timestamp in US format (MM/DD/YYYY at HH:MM a.m./p.m.).
- Handles HTTP errors and network exceptions gracefully with detailed error messages (connection failures, rate limits, invalid JSON).
- Implements retry logic for temporary API failures (connection issues, rate limits, server errors).
- Uses a static HTTP client to optimize API requests and reduce connection overhead.
- Clears console for clean, real-time updates using native ANSI codes.
- Supports UTF-8 encoding for proper character display (colors and special characters).
- Centralized formatted output for consistent display using a generic function.
- Caches formatted timestamps to avoid redundant computations.
- Organizes ANSI color codes in a namespace for better code structure.
- Supports clean program exit with 'q' (followed by Enter) or Ctrl+C.
- Displays an ASCII progress bar during the 60-second wait period, showing progress and time remaining.
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
| **OS**             | Windows (tested with MSYS2 UCRT64); Linux/macOS (with adjustments) | CMake ensures cross-platform compatibility; UTF-8 support required for ANSI colors and progress bar |

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

> [!NOTE]
> To exit the program, press 'q' followed by Enter or use Ctrl+C. The progress bar updates every second to indicate the time remaining until the next price fetch.

<br>

## Project Structure 🗂️
```bash
btc-price-tracker/
├── include/                    // Header files for external libraries
│   ├── httplib.h               // HTTP client library (cpp-httplib): https://github.com/yhirose/cpp-httplib
│   ├── json.hpp                // JSON parsing library (nlohmann/json): https://github.com/nlohmann/json
├── src/                        // Source code
│   ├── main.cpp                // Main application (fetches and displays Bitcoin price)
├── docs/						// Additional files
│   ├── CHANGELOG.md			// Change history
│   └── USER_GUIDE.md			// User documentation
├── LICENSE                     // MIT License file
├── CMakeLists.txt              // CMake build configuration for cross-platform builds
└── README.md                   // Project documentation
```

<br>

## Contributing 🤝

Contributions are welcome! To contribute:

- Fork the repository.
- Create a new branch (`git checkout -b feature/your-feature`).
- Make your changes and commit them (`git commit -m "Add your feature"`).
- Push to the branch (`git push origin feature/your-feature`).
- Open a pull request on GitHub.

Please ensure your code follows the project's coding style and includes appropriate documentation.

<br>

## License 🧾

This project is licensed under the **MIT License** - see the LICENSE file for details.

<br>

## Crédits ☕

> Developed by PHForge. 
> Feel free to reach out via [GitHub](https://github.com/PHForge) for feedback or collaboration ideas!

> Special thanks ❤️ to my wife and son for their patience and love.

