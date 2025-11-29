#!/bin/bash

# Start Chrome with remote debugging enabled
# This allows Selenium to connect to an already-running Chrome instance

PORT=9222

echo "Starting Chrome with remote debugging on port $PORT..."
echo "This will keep your login session active and bypass Cloudflare checks"
echo ""

# Kill any existing Chrome instances
pkill -f "chrome.*remote-debugging-port"

# Wait a moment
sleep 1

# Start Chrome with remote debugging
google-chrome --remote-debugging-port=$PORT --user-data-dir="$HOME/.config/google-chrome" &

echo ""
echo "✓ Chrome started!"
echo ""
echo "Now:"
echo "1. Login to Codeforces in the browser"
echo "2. Complete any Cloudflare checks"
echo "3. Keep this Chrome window open"
echo "4. Run: python submit.py <problem_code>"
echo ""
echo "Press Ctrl+C to stop this script (Chrome will keep running)"

# Keep script running
wait