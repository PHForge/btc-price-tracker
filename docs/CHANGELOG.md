# Changelog

All notable changes to the Bitcoin Price Tracker project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1] - 2025-07-05

### Added
- Clean program exit with 'q' (followed by Enter) or Ctrl+C, using a separate thread and signal handling.
- ASCII progress bar animation during the 60-second wait period, showing progress percentage and time remaining.
- Contributing section in `README.md` to encourage community contributions.
- Note in `README.md` about exit instructions and progress bar behavior.

### Changed
- Updated `README.md` to reflect version 0.1, including new features and adjusted example output.
- Updated `CMakeLists.txt` to set project version to 0.1.
- Improved message in `main` to clarify exit instructions ("Press 'q' then Enter or Ctrl+C to exit").
- Adjusted progress bar positioning for better alignment in the console output.

## [0.0.9] - 2025-07-01

### Fixed
- Fixed clean exit functionality:
  - Corrected 'q' keypress handling by clearing the input buffer to prevent character display.
  - Replaced 60-second sleep with 1-second intervals to check exit condition more frequently, improving Ctrl+C responsiveness.
- Updated version to 0.0.9 in code comments.

### Added
- `<limits>` header for input buffer clearing in `listenForExitKey`.

## [0.0.8] - 2025-06-28

### Added
- `Colors` namespace to organize ANSI color codes and `CLEAR_SCREEN` constant, reducing global scope pollution.
- Timestamp caching in `getCurrentTimeFormatted` to avoid redundant formatting within the same second.

### Changed
- Updated all references to ANSI color constants to use `Colors::` prefix.
- Updated `README.md` to reflect version 0.0.8, adding new features and UTF-8 support note.

## [0.0.7] - 2025-06-16

### Added
- Initial release of Bitcoin Price Tracker.
- Fetches Bitcoin price in USD from CoinGecko API every 60 seconds.
- Displays price and timestamp in US format (MM/DD/YYYY HH:MM AM/PM).
- Handles HTTP errors and network exceptions with detailed messages (connection failures, rate limits, invalid JSON).
- Implements retry logic for temporary API failures (connection issues, rate limits, server errors).
- Uses a static HTTP client to optimize API requests.
- Clears console with native ANSI codes for real-time updates.
- Supports UTF-8 encoding for proper character display.
- Centralized formatted output with `printFormattedLine` for consistent display.
- Cross-platform build system using CMake, compatible with Windows, Linux, and macOS.