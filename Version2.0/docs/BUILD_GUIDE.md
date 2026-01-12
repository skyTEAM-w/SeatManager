# SeatManager 2.0 - Build and Installation Guide

## Overview

This guide provides detailed instructions for building and installing SeatManager 2.0 on different operating systems.

## Prerequisites

### Common Requirements
- Python 3.7 or higher
- pip (Python package manager)
- CMake 3.12 or higher
- C++17 compatible compiler

### Platform-Specific Requirements

#### Windows
- Visual Studio 2019 or later (with C++ development tools)
- Windows 10 or later

#### macOS
- Xcode Command Line Tools
- macOS 10.14 (Mojave) or later

#### Linux (Ubuntu/Debian)
- GCC 7 or later
- build-essential package
- Python 3 development headers

## Installation Steps

### Step 1: Clone or Download the Project

```bash
# If using git
git clone <repository-url>
cd SeatManager/Version2.0

# Or download and extract the archive
cd SeatManager/Version2.0
```

### Step 2: Create Python Virtual Environment

#### Windows
```bash
python -m venv venv
venv\Scripts\activate
```

#### macOS/Linux
```bash
python3 -m venv venv
source venv/bin/activate
```

### Step 3: Install Python Dependencies

```bash
pip install --upgrade pip
pip install -r requirements.txt
```

### Step 4: Build C++ Backend

#### Windows (MSVC)

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release
cd ..
```

Alternative using Visual Studio IDE:
1. Open `backend/CMakeLists.txt` in Visual Studio
2. Select "Release" configuration
3. Build the solution

#### macOS (Xcode)

```bash
mkdir build
cd build
cmake .. -G "Xcode"
cmake --build . --config Release
cd ..
```

#### Linux (GCC)

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
cd ..
```

### Step 5: Install Python Package

```bash
pip install -e .
```

This command installs the package in development mode, allowing you to make changes without reinstalling.

## Verification

### Test Installation

```bash
python -c "import seatmanager_backend; print('Backend loaded successfully')"
```

If successful, you should see: "Backend loaded successfully"

### Run Tests

```bash
pytest backend/tests/
```

### Launch Application

```bash
python main.py
```

## Troubleshooting

### Common Issues

#### Issue: "CMake not found"

**Solution**: Install CMake from [cmake.org](https://cmake.org/download/) or use package manager:
- Windows: Download installer
- macOS: `brew install cmake`
- Linux: `sudo apt install cmake`

#### Issue: "pybind11 not found"

**Solution**: Install pybind11:
```bash
pip install pybind11
```

#### Issue: "Visual Studio not found" (Windows)

**Solution**: 
1. Install Visual Studio 2019 or later
2. During installation, select "Desktop development with C++"
3. Ensure CMake can find the compiler: `cmake --help`

#### Issue: "Python.h not found" (Linux)

**Solution**: Install Python development headers:
```bash
sudo apt install python3-dev
```

#### Issue: "ModuleNotFoundError: No module named 'PyQt5'"

**Solution**: Install PyQt5:
```bash
pip install PyQt5
```

#### Issue: Build fails with C++ errors

**Solution**: Ensure your compiler supports C++17:
- Windows: Visual Studio 2017 or later
- macOS: Xcode 9.3 or later
- Linux: GCC 7 or later with `-std=c++17` flag

## Advanced Configuration

### Custom Build Options

You can customize the build by passing CMake options:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
```

### Building Without Virtual Environment

If you prefer not to use a virtual environment:

```bash
pip install --user -r requirements.txt
pip install --user -e .
```

### Creating Distribution Package

#### Windows (Executable)

```bash
pip install pyinstaller
pyinstaller --onefile --windowed main.py
```

The executable will be in `dist/main.exe`

#### macOS (Application Bundle)

```bash
pip install pyinstaller
pyinstaller --onefile --windowed --icon=app.icns main.py
```

#### Linux (Binary)

```bash
pip install pyinstaller
pyinstaller --onefile main.py
```

## Development Setup

### Setting Up IDE

#### Visual Studio Code
1. Install Python extension
2. Install C/C++ extension
3. Open the project folder
4. Select Python interpreter from virtual environment

#### PyCharm
1. Open project
2. File → Settings → Project → Python Interpreter
3. Add new interpreter → Existing environment
4. Select `venv/Scripts/python.exe` (Windows) or `venv/bin/python` (macOS/Linux)

#### CLion
1. Open project
2. File → Settings → Build, Execution, Deployment → CMake
3. Configure CMake options
4. Build and run

### Running Tests

```bash
# Run all tests
pytest backend/tests/

# Run specific test file
pytest backend/tests/test_backend.py

# Run with verbose output
pytest -v backend/tests/

# Run with coverage
pytest --cov=seatmanager_backend backend/tests/
```

### Debugging

#### Python Code
```bash
python -m pdb main.py
```

#### C++ Code
Use your IDE's debugger or:
```bash
gdb python
(gdb) run main.py
```

## Clean Build

To start fresh:

```bash
# Remove build artifacts
rm -rf build/
rm -rf __pycache__/
rm -rf *.egg-info/
find . -type d -name __pycache__ -exec rm -rf {} +
find . -type f -name "*.pyc" -delete

# Rebuild
mkdir build
cd build
cmake ..
make -j$(nproc)
cd ..
pip install -e .
```

## Performance Optimization

### Compiler Optimizations

For release builds, enable optimizations:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

### Python Optimizations

Use PyPy for better performance (experimental):
```bash
pip install pypy3
pypy3 -m pip install -r requirements.txt
pypy3 main.py
```

## Uninstallation

### Remove Python Package

```bash
pip uninstall seatmanager
```

### Remove Virtual Environment

```bash
deactivate
rm -rf venv/
```

### Remove Build Artifacts

```bash
rm -rf build/
```

## Additional Resources

- [CMake Documentation](https://cmake.org/documentation/)
- [pybind11 Documentation](https://pybind11.readthedocs.io/)
- [PyQt5 Documentation](https://www.riverbankcomputing.com/static/Docs/PyQt5/)
- [Python Packaging Guide](https://packaging.python.org/)

## Support

For build-related issues, please:
1. Check the troubleshooting section above
2. Review error messages carefully
3. Ensure all prerequisites are met
4. Consult the project documentation

---

*Last Updated: 2026*