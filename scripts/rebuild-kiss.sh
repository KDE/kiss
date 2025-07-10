#!/bin/bash

# Expects to be run from the kiss source directory, eg:
# ./scripts/rebuild-kiss.sh

set -e

# Use a consistent named temporary build directory
BUILD_DIR="/tmp/kiss-build"

# Try to uninstall if the build directory already exists
if [ -d "$BUILD_DIR" ]; then
  # Use || true to prevent uninstall failure from stopping the script
  sudo cmake --build $BUILD_DIR --target uninstall || true
  # Remove build directory to start fresh
  rm -rf "$BUILD_DIR"
fi

# Create build directory if it doesn't exist
mkdir -p $BUILD_DIR

cmake -B $BUILD_DIR
cmake --build $BUILD_DIR --parallel --config RelWithDebInfo
sudo cmake --install $BUILD_DIR --config RelWithDebInfo

# Keep the build directory for future uninstall operations
echo "Build completed. Build directory preserved at $BUILD_DIR for future uninstall operations."
