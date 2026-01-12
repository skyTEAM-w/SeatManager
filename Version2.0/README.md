# SeatManager 2.0

A comprehensive classroom seating management system with C++ backend and Python GUI frontend.

## Features

### Core Functionality
- **Visual Seating Chart**: Interactive graphical representation of classroom seating arrangements
- **Drag-and-Drop**: Manual seat assignment adjustments via intuitive drag-and-drop interface (supports swapping seats)
- **Multiple Assignment Algorithms**:
  - Random assignment
  - Alphabetical assignment
  - ID-based assignment
  - Custom assignment
- **File Import/Export**: Support for CSV, TXT, and JSON formats
- **Classroom Configuration**: Flexible classroom layout settings including:
  - Customizable dimensions (rows × columns)
  - Multiple aisle layout options:
    - No aisles
    - Single center aisle
    - Dual side aisles
    - Custom aisle placement
- **Student Management**: Add, remove, and search students with metadata (name, gender, class)
- **Save/Load Configurations**: Persist classroom and seating configurations

### Technical Architecture
- **Backend**: C++ for efficient data handling and algorithm execution
- **Frontend**: Python with PyQt5 for graphical user interface
- **Integration**: pybind11 bindings for seamless C++/Python interoperability
- **Performance**: Optimized for handling large classrooms (O(log N) assignment complexity) with thread safety
- **Thread Safety**: Full thread-safe backend implementation using recursive mutexes

## Installation

### Prerequisites
- Python 3.7 or higher
- C++ compiler with C++17 support (MSVC on Windows, GCC on Linux, Clang on macOS)
- CMake 3.12 or higher

### Build Instructions

#### Windows (MSVC)
```bash
cd Version2.0
python -m venv venv
venv\Scripts\activate
pip install -r requirements.txt

# Build C++ backend
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
cd ..

# Build Python package
pip install -e .
```

#### Linux/macOS
```bash
cd Version2.0
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt

# Build C++ backend
mkdir build
cd build
cmake ..
make -j4
cd ..

# Build Python package
pip install -e .
```

## Usage

### Running the Application
```bash
python main.py
```

### Basic Workflow

1. **Configure Classroom**
   - Go to Edit → Configure Classroom
   - Set number of rows and columns
   - Choose aisle layout type
   - Click OK to apply

2. **Import Students**
   - Go to File → Import Students
   - Select a CSV, TXT, or JSON file
   - Students will be loaded into the student list

3. **Assign Seats**
   - Use toolbar buttons or Tools menu:
     - **Random**: Randomly assign students to seats
     - **Alpha**: Assign students alphabetically by name
     - **By ID**: Assign students in ID order
   - Or drag-and-drop students to manually adjust

4. **Export Results**
   - Go to File → Export Seating Chart
   - Choose format (CSV, TXT, or JSON)
   - Save to desired location

5. **Save Configuration**
   - Go to File → Save Configuration
   - Save classroom layout and student assignments for later use

## File Formats

### CSV Format
```csv
Name,Gender,Class,ID
John Doe,Male,Class 1A,1
Jane Smith,Female,Class 1A,2
```

### TXT Format
```
John Doe
Jane Smith
```

### JSON Format
```json
{
  "classroom": {
    "rows": 8,
    "cols": 6,
    "aisleLayout": 1
  },
  "students": [
    {
      "id": 1,
      "name": "John Doe",
      "gender": "Male",
      "className": "Class 1A"
    }
  ],
  "assignments": [
    {
      "studentId": 1,
      "row": 0,
      "col": 0
    }
  ]
}
```

## Keyboard Shortcuts

- `Ctrl+I`: Import Students
- `Ctrl+E`: Export Seating Chart
- `Ctrl+S`: Save Configuration
- `Ctrl+O`: Load Configuration
- `Ctrl+N`: Add Student
- `Ctrl+Q`: Exit
- `F5`: Refresh View

## Architecture

### Backend (C++)
- **Student**: Represents a student with ID, name, gender, and class
- **Seat**: Represents a seat with position, type, and occupancy status
- **Classroom**: Manages classroom layout including dimensions and aisles
- **SeatManager**: Core logic for seat assignment and student management

### Frontend (Python/PyQt5)
- **MainWindow**: Main application window with menu and toolbar
- **SeatingChartWidget**: Visual representation of seating with drag-and-drop
- **ClassroomConfigDialog**: Classroom configuration interface
- **StudentListWidget**: Student list with search functionality
- **FileHandler**: File I/O operations for various formats

## Performance

- Optimized for classrooms with up to 200 students
- Efficient C++ backend for fast algorithm execution
- Responsive GUI with minimal latency

## Testing

Run the test suite:
```bash
pytest backend/tests/
```

## Troubleshooting

### Backend Not Available
If you see "Warning: C++ backend not available", ensure:
1. C++ backend is built successfully
2. Python package is installed with `pip install -e .`
3. pybind11 is installed correctly

### Import Errors
If you encounter import errors:
1. Ensure all dependencies are installed: `pip install -r requirements.txt`
2. Check Python version is 3.7 or higher
3. Verify C++ compiler is installed and accessible

## License

This project is provided as-is for educational and commercial use.

## Version History

### Version 2.0.0
- Complete rewrite with C++ backend and Python GUI
- Visual seating chart with drag-and-drop
- Multiple assignment algorithms
- Comprehensive file I/O support
- Configurable classroom layouts
- Performance optimizations

### Previous Versions
- 1.8.x: Java and Python versions
- 1.7.2: C++ console version

## Support

For issues, questions, or contributions, please refer to the project documentation.