#!/bin/bash

# SPDX-FileCopyrightText: 2025 Kristen McWilliam <kristen@kde.org>
#
# SPDX-License-Identifier: LGPL-2.1-or-later

# A simple script to (re)build KISS from source for testing during development.
# 
# This makes (re)building KISS easier because it should be done in a VM during 
# development, to prevent breaking the host system.
# 
# Expects to be run from the kiss source directory, eg:
# ./scripts/rebuild-dev.sh

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
