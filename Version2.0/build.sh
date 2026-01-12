#!/bin/bash

# SeatManager 2.0 Build Script for macOS/Linux

set -e

echo "===================================="
echo "SeatManager 2.0 Build Script"
echo "===================================="
echo ""

# Check if Python 3 is installed
if ! command -v python3 &> /dev/null; then
    echo "ERROR: Python 3 is not installed"
    echo "Please install Python 3.7 or higher"
    exit 1
fi

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake is not installed"
    echo "Please install CMake 3.12 or higher"
    exit 1
fi

echo "[1/6] Creating virtual environment..."
python3 -m venv venv

echo "[2/6] Activating virtual environment..."
source venv/bin/activate

echo "[3/6] Installing Python dependencies..."
pip install --upgrade pip
pip install -r requirements.txt

echo "[4/6] Creating build directory..."
mkdir -p build
cd build

echo "[5/6] Building C++ backend with CMake..."
cmake ../backend
if [ "$(uname)" == "Darwin" ]; then
    # macOS
    cmake --build . --config Release
else
    # Linux
    make -j$(nproc)
fi

cd ..

echo "[6/6] Installing Python package..."
pip install -e .

echo ""
echo "===================================="
echo "Build completed successfully!"
echo "===================================="
echo ""
echo "To run the application:"
echo "  source venv/bin/activate"
echo "  python main.py"
echo ""
echo "To run tests:"
echo "  pytest backend/tests/"
echo ""