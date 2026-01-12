@echo off
REM SeatManager 2.0 Build Script for Windows

echo ====================================
echo SeatManager 2.0 Build Script
echo ====================================
echo.

REM Check if Python is installed
python --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: Python is not installed or not in PATH
    echo Please install Python 3.7 or higher from https://www.python.org/
    pause
    exit /b 1
)

echo [1/6] Creating virtual environment...
python -m venv venv
if errorlevel 1 (
    echo ERROR: Failed to create virtual environment
    pause
    exit /b 1
)

echo [2/6] Activating virtual environment...
call venv\Scripts\activate.bat
if errorlevel 1 (
    echo ERROR: Failed to activate virtual environment
    pause
    exit /b 1
)

echo [3/6] Installing Python dependencies...
pip install --upgrade pip
pip install -r requirements.txt
if errorlevel 1 (
    echo ERROR: Failed to install Python dependencies
    pause
    exit /b 1
)

echo [4/6] Creating build directory...
if not exist build mkdir build
cd build

echo [5/6] Building C++ backend with CMake...
cmake ../backend -G "Visual Studio 16 2019" -A x64
if errorlevel 1 (
    echo ERROR: CMake configuration failed
    echo Please ensure Visual Studio 2019 or later is installed with C++ tools
    cd ..
    pause
    exit /b 1
)

cmake --build . --config Release
if errorlevel 1 (
    echo ERROR: C++ backend build failed
    cd ..
    pause
    exit /b 1
)

cd ..

echo [6/6] Installing Python package...
pip install -e .
if errorlevel 1 (
    echo ERROR: Failed to install Python package
    pause
    exit /b 1
)

echo.
echo ====================================
echo Build completed successfully!
echo ====================================
echo.
echo To run the application:
echo   venv\Scripts\activate
echo   python main.py
echo.
echo To run tests:
echo   pytest backend/tests/
echo.
pause