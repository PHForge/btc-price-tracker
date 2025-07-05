
# Bitcoin Price Tracker - User Guide

  

## Overview

Bitcoin Price Tracker is a console-based application that fetches and displays the real-time Bitcoin price in USD from the CoinGecko API every 60 seconds. It features a clean, color-coded interface with an ASCII progress bar to indicate the time until the next update.

  

## Usage

1.  **Run the Program**:

- After building (see `README.md` for installation), run the executable:

	```bash

	./btc-price-tracker # Linux/macOS

	./btc-price-tracker.exe # Windows

	```
<br>

2.  **View the Output**:

- The console displays:

- The current Bitcoin price (in green) or an error message (in red).

- The timestamp of the last update (in cyan).

- A progress bar showing the time remaining until the next update (in yellow).

- Instructions to exit ("press 'q' then Enter or Ctrl+C").

<br>

3.  **Exit the Program**:

- Press `q` followed by Enter to exit gracefully.

- Alternatively, press `Ctrl+C` to exit immediately.

- A farewell message is displayed upon exit.

<br>

## Features

-  **Real-time Price Updates**: Fetches Bitcoin price every 60 seconds.

-  **Error Handling**: Displays detailed error messages for network or API issues.

-  **Progress Bar**: Shows a visual countdown during the wait period.

-  **Cross-Platform**: Works on Windows, Linux, and macOS with UTF-8 support.

-  **Clean Exit**: Supports exiting with `q` (then Enter) or `Ctrl+C`.

<br>  

## Troubleshooting

-  **Progress Bar Misaligned**: Ensure your terminal supports UTF-8 and ANSI escape codes.

-  **API Errors**: Check your internet connection or try again later if the CoinGecko API is unavailable.

-  **Exit Issues**: If `q` doesn’t work, ensure you press Enter after `q`. Use `Ctrl+C` for immediate exit.

 <br>

## Feedback

For issues or suggestions, open an issue on the [GitHub repository](https://github.com/PHForge/btc-price-tracker) or contact PHForge via GitHub.