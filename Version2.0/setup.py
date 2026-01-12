from setuptools import setup, Extension, find_packages
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir
import pybind11
from pathlib import Path

ext_modules = [
    Pybind11Extension(
        "seatmanager_backend",
        [
            "backend/src/Student.cpp",
            "backend/src/Seat.cpp",
            "backend/src/Classroom.cpp",
            "backend/src/SeatManager.cpp",
            "backend/src/bindings.cpp",
        ],
        include_dirs=[
            "backend/include",
            pybind11.get_include(),
        ],
        cxx_std=17,
    ),
]

setup(
    name="seatmanager",
    version="2.0.0",
    author="SeatManager Team",
    description="Classroom Seating Management System - Version 2.0",
    long_description=Path("README.md").read_text(encoding="utf-8") if Path("README.md").exists() else "",
    long_description_content_type="text/markdown",
    url="https://github.com/your-org/SeatManager",
    packages=find_packages(include=["frontend", "frontend.*"]),
    include_package_data=True,
    install_requires=[
        "PyQt5>=5.15.0",
        "pybind11>=2.10.0",
        "openpyxl>=3.0.0",
    ],
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    python_requires=">=3.7",
    classifiers=[
        "Programming Language :: Python :: 3",
        "Programming Language :: C++",
        "Operating System :: Microsoft :: Windows",
        "License :: OSI Approved :: MIT License",
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Education",
        "Topic :: Education",
        "Topic :: Software Development :: Build Tools",
        "Topic :: Utilities",
    ],
    entry_points={
        "console_scripts": [
            "seatmanager=main:main",
        ]
    },
)
