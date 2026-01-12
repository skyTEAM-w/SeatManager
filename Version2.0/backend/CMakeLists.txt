cmake_minimum_required(VERSION 3.12)
project(SeatManager VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

set(PYTHON_EXECUTABLE "${CMAKE_SOURCE_DIR}/../venv/Scripts/python.exe")
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/../venv/Lib/site-packages/pybind11/share/cmake/pybind11")

find_package(pybind11 REQUIRED)

pybind11_add_module(seatmanager_backend
    src/Student.cpp
    src/Seat.cpp
    src/Classroom.cpp
    src/SeatManager.cpp
    src/bindings.cpp
)

target_include_directories(seatmanager_backend PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(seatmanager_backend PRIVATE /W4)
else()
    target_compile_options(seatmanager_backend PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(APPLE)
    set_target_properties(seatmanager_backend PROPERTIES
        LINK_FLAGS "-undefined dynamic_lookup"
    )
endif()