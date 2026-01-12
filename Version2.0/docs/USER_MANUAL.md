# SeatManager 2.0 User Manual

## Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Getting Started](#getting-started)
4. [Classroom Configuration](#classroom-configuration)
5. [Student Management](#student-management)
6. [Seat Assignment](#seat-assignment)
7. [File Operations](#file-operations)
8. [Advanced Features](#advanced-features)
9. [Troubleshooting](#troubleshooting)
10. [FAQ](#faq)

---

## Introduction

SeatManager 2.0 is a comprehensive classroom seating management system designed to help teachers and administrators efficiently organize student seating arrangements. The application combines a powerful C++ backend for fast processing with an intuitive Python-based graphical interface.

### Key Features
- **Visual Seating Chart**: Interactive graphical representation of classroom layouts
- **Drag-and-Drop**: Easily adjust seat assignments by dragging students
- **Multiple Algorithms**: Choose from random, alphabetical, or ID-based assignment
- **Flexible Layouts**: Configure classrooms with various aisle arrangements
- **File Support**: Import/export students and configurations in multiple formats
- **Performance**: Handles up to 200 students efficiently

---

## Installation

### System Requirements
- **Operating System**: Windows 10/11, macOS 10.14+, or Linux (Ubuntu 18.04+)
- **Python**: Version 3.7 or higher
- **Memory**: Minimum 4GB RAM (8GB recommended)
- **Storage**: 100MB free space
- **Compiler**: C++17 compatible compiler (MSVC, GCC, or Clang)

### Installation Steps

#### Windows
1. Install Python 3.7+ from [python.org](https://www.python.org/downloads/)
2. Install Visual Studio 2019 or later with C++ development tools
3. Download and extract SeatManager 2.0
4. Open Command Prompt in the extracted directory
5. Run the following commands:
   ```bash
   python -m venv venv
   venv\Scripts\activate
   pip install -r requirements.txt
   mkdir build
   cd build
   cmake .. -G "Visual Studio 16 2019"
   cmake --build . --config Release
   cd ..
   pip install -e .
   ```

#### macOS
1. Install Python 3.7+ using Homebrew: `brew install python3`
2. Install Xcode Command Line Tools: `xcode-select --install`
3. Download and extract SeatManager 2.0
4. Open Terminal in the extracted directory
5. Run the following commands:
   ```bash
   python3 -m venv venv
   source venv/bin/activate
   pip install -r requirements.txt
   mkdir build
   cd build
   cmake ..
   make -j4
   cd ..
   pip install -e .
   ```

#### Linux (Ubuntu)
1. Install dependencies:
   ```bash
   sudo apt update
   sudo apt install python3 python3-pip python3-venv cmake build-essential
   ```
2. Download and extract SeatManager 2.0
3. Open Terminal in the extracted directory
4. Run the following commands:
   ```bash
   python3 -m venv venv
   source venv/bin/activate
   pip install -r requirements.txt
   mkdir build
   cd build
   cmake ..
   make -j4
   cd ..
   pip install -e .
   ```

---

## Getting Started

### Launching the Application

#### Windows
```bash
venv\Scripts\activate
python main.py
```

#### macOS/Linux
```bash
source venv/bin/activate
python main.py
```

### First-Time Setup

When you first launch SeatManager 2.0, you'll see the main interface with:
- **Left Panel**: Student list
- **Right Panel**: Seating chart
- **Top Toolbar**: Quick access buttons
- **Menu Bar**: Full feature access

The default classroom is configured as 8 rows × 6 columns with a center aisle.

---

## Classroom Configuration

### Accessing Configuration
1. Go to **Edit → Configure Classroom** or click the **Configure** button on the toolbar
2. The Classroom Configuration dialog will appear

### Setting Dimensions
- **Number of Rows**: Enter the desired number of rows (1-20)
- **Number of Columns**: Enter the desired number of columns (1-20)

### Choosing Aisle Layout

#### No Aisles
- All seats are arranged in a continuous grid
- Maximum seating capacity

#### Single Center Aisle
- One aisle runs down the center of the classroom
- Provides easy access to all rows
- Reduces total seat count by approximately 1/number of columns

#### Dual Side Aisles
- Two aisles divide the classroom into three sections
- Common in larger classrooms
- Reduces total seat count by approximately 2/number of columns

#### Custom Aisles
- Specify exact column positions for aisles
- Use the spin box to select a column number
- Click "Add Aisle" to add it to the list
- Select an aisle and click "Remove Selected" to remove it
- Click "Update Preview" to see the layout

### Preview
The preview area shows a visual representation of your classroom configuration:
- `[ ]` represents a seat
- Spaces represent aisles

### Applying Configuration
Click **OK** to apply the configuration or **Cancel** to discard changes.

---

## Student Management

### Adding Students

#### Manual Entry
1. Click the **Add Student** button in the left panel
2. Enter student information:
   - **Name**: Required field
   - **Gender**: Optional (Male, Female, Other)
   - **Class**: Optional (e.g., "Class 1A")
3. Click **OK** to add the student

#### Importing from File
1. Go to **File → Import Students** or press `Ctrl+I`
2. Select a file (CSV, TXT, or JSON format)
3. Students will be imported automatically

### Viewing Students
- All students are displayed in the left panel
- Use the search box to filter students by name
- Click on a student to select them

### Removing Students
1. Select a student from the list
2. Click the **Remove Selected** button
3. Confirm the removal if prompted

### Student Information
Click on any student in the seating chart to view their details:
- Name
- ID
- Gender
- Class
- Current seat position

---

## Seat Assignment

### Automatic Assignment

#### Random Assignment
1. Import or add students to the list
2. Click the **Random** button or go to **Tools → Assign Random**
3. Students will be randomly assigned to available seats

#### Alphabetical Assignment
1. Import or add students to the list
2. Click the **Alpha** button or go to **Tools → Assign Alphabetical**
3. Students will be assigned in alphabetical order by name

#### ID-Based Assignment
1. Import or add students to the list
2. Click the **By ID** button or go to **Tools → Assign by ID**
3. Students will be assigned in order of their ID numbers

### Manual Assignment (Drag-and-Drop)
1. Click and hold on a student in the seating chart
2. Drag the student to the desired seat
3. Release the mouse button to place the student
4. If the target seat is empty, the student will be moved
5. If the target seat is occupied, the two students will swap positions

### Clearing Assignments
- Click the **Clear** button or go to **Tools → Clear All Assignments**
- All students will be removed from seats
- Students remain in the student list

### Assignment Validation
The system automatically validates assignments to ensure:
- No two students are assigned to the same seat
- Students are not assigned to aisles
- All assignments are within classroom boundaries

---

## File Operations

### Importing Students

#### Supported Formats
- **CSV**: Comma-separated values with headers
- **TXT**: Plain text with one name per line
- **JSON**: Structured data format

#### CSV Format Example
```csv
Name,Gender,Class
John Doe,Male,Class 1A
Jane Smith,Female,Class 1B
```

#### TXT Format Example
```
John Doe
Jane Smith
```

#### JSON Format Example
```json
{
  "students": [
    {
      "id": 1,
      "name": "John Doe",
      "gender": "Male",
      "className": "Class 1A"
    }
  ]
}
```

### Exporting Seating Charts

#### Export Options
1. Go to **File → Export Seating Chart** or press `Ctrl+E`
2. Choose the desired format:
   - **CSV**: Spreadsheet-compatible format
   - **TXT**: Plain text format
   - **JSON**: Structured data format
3. Select a save location
4. Click **Save**

### Saving Configurations

1. Go to **File → Save Configuration** or press `Ctrl+S`
2. Choose a save location
3. The configuration will be saved as a JSON file including:
   - Classroom dimensions
   - Aisle layout
   - Student list
   - Current seat assignments

### Loading Configurations

1. Go to **File → Load Configuration** or press `Ctrl+O`
2. Select a previously saved JSON configuration file
3. The classroom and all assignments will be restored

---

## Advanced Features

### Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| `Ctrl+I` | Import Students |
| `Ctrl+E` | Export Seating Chart |
| `Ctrl+S` | Save Configuration |
| `Ctrl+O` | Load Configuration |
| `Ctrl+N` | Add Student |
| `Ctrl+Q` | Exit Application |
| `F5` | Refresh View |

### Status Bar Information
The status bar at the bottom displays:
- Classroom dimensions (rows × columns)
- Total number of seats
- Number of occupied seats
- Number of available seats

### Student Search
- Use the search box in the student list panel
- Type any part of a student's name
- The list filters in real-time as you type

### Multiple Seating Charts
- Generate multiple seating arrangements
- Export each arrangement to a separate file
- Compare different configurations

### Performance Optimization
- The system is optimized for up to 200 students
- Large classrooms (20×20) are supported
- Drag-and-drop operations are smooth and responsive

---

## Troubleshooting

### Backend Not Available

**Problem**: "Warning: C++ backend not available" message appears

**Solutions**:
1. Ensure the C++ backend is built successfully
2. Run `pip install -e .` to install the Python package
3. Verify pybind11 is installed: `pip list | grep pybind11`
4. Check that your C++ compiler is properly configured

### Import Errors

**Problem**: Cannot import students from a file

**Solutions**:
1. Verify the file format is correct (CSV, TXT, or JSON)
2. Check that the file is not corrupted
3. Ensure the file encoding is UTF-8
4. Try opening the file in a text editor to verify content

### Assignment Issues

**Problem**: Students not assigned correctly

**Solutions**:
1. Ensure there are enough available seats
2. Check that aisles are not blocking seat access
3. Verify the classroom configuration
4. Try clearing assignments and re-assigning

### Drag-and-Drop Not Working

**Problem**: Cannot drag students to new seats or swap seats

**Solutions**:
1. Ensure the target seat is not an aisle
2. Verify the student is properly selected
3. Try clicking and holding for a moment before dragging
4. If swapping, ensure both seats are valid normal seats

### Performance Issues

**Problem**: Application is slow or unresponsive

**Solutions**:
1. Reduce the number of students (maximum 200 recommended)
2. Close other applications to free up memory
3. Restart the application
4. Check system resources (CPU, memory)

---

## FAQ

### Q: Can I have multiple classrooms?
A: Currently, SeatManager 2.0 supports one classroom at a time. You can save different configurations as separate JSON files and load them as needed.

### Q: What is the maximum number of students?
A: The system is optimized for up to 200 students, but it can handle more depending on your system resources.

### Q: Can I customize the seat colors?
A: Seat colors are currently fixed (blue for occupied, white for empty, gray for aisles). Customization may be added in future versions.

### Q: Is my data saved automatically?
A: No, you must manually save your configuration using **File → Save Configuration** or `Ctrl+S`.

### Q: Can I print the seating chart?
A: Currently, there is no direct print function. Export the seating chart to a format compatible with your preferred application and print from there.

### Q: Does the application work on mobile devices?
A: SeatManager 2.0 is designed for desktop use. Mobile support may be considered for future versions.

### Q: Can I share configurations with other users?
A: Yes, save your configuration as a JSON file and share it. Other users can load it using **File → Load Configuration**.

### Q: What happens if I have more students than seats?
A: Only the first N students (where N equals the number of available seats) will be assigned. The remaining students will remain in the student list but unseated.

### Q: Can I undo an assignment?
A: There is no undo function, but you can clear all assignments and re-assign, or manually move students using drag-and-drop.

### Q: Is the application available in other languages?
A: Currently, SeatManager 2.0 is available in English only. Multi-language support may be added in future versions.

---

## Support

For additional help, questions, or feature requests, please refer to the project documentation or contact the development team.

---

## Version Information

**Version**: 2.0.0  
**Release Date**: 2026  
**Platform**: Windows, macOS, Linux  

---

*End of User Manual*