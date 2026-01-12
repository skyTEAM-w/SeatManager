#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Student.h"
#include "Seat.h"
#include "Classroom.h"
#include "SeatManager.h"

namespace py = pybind11;

PYBIND11_MODULE(seatmanager_backend, m) {
    m.doc() = "SeatManager Backend - C++ Core Library";
    
    py::enum_<seatmanager::SeatType>(m, "SeatType")
        .value("NORMAL", seatmanager::SeatType::NORMAL)
        .value("AISLE", seatmanager::SeatType::AISLE)
        .value("EMPTY", seatmanager::SeatType::EMPTY)
        .export_values();
    
    py::enum_<seatmanager::AisleLayout>(m, "AisleLayout")
        .value("NONE", seatmanager::AisleLayout::NONE)
        .value("CENTER", seatmanager::AisleLayout::CENTER)
        .value("DUAL_SIDE", seatmanager::AisleLayout::DUAL_SIDE)
        .value("CUSTOM", seatmanager::AisleLayout::CUSTOM)
        .export_values();
    
    py::enum_<seatmanager::AssignmentAlgorithm>(m, "AssignmentAlgorithm")
        .value("RANDOM", seatmanager::AssignmentAlgorithm::RANDOM)
        .value("ALPHABETICAL", seatmanager::AssignmentAlgorithm::ALPHABETICAL)
        .value("ID_ORDER", seatmanager::AssignmentAlgorithm::ID_ORDER)
        .value("CUSTOM", seatmanager::AssignmentAlgorithm::CUSTOM)
        .export_values();
    
    py::class_<seatmanager::Student>(m, "Student")
        .def(py::init<>())
        .def(py::init<const std::string&, int>())
        .def(py::init<const std::string&, int, const std::string&, const std::string&>())
        .def("getName", &seatmanager::Student::getName)
        .def("setName", &seatmanager::Student::setName)
        .def("getId", &seatmanager::Student::getId)
        .def("setId", &seatmanager::Student::setId)
        .def("getGender", &seatmanager::Student::getGender)
        .def("setGender", &seatmanager::Student::setGender)
        .def("getClassName", &seatmanager::Student::getClassName)
        .def("setClassName", &seatmanager::Student::setClassName)
        .def("__eq__", &seatmanager::Student::operator==)
        .def("__lt__", &seatmanager::Student::operator<)
        .def("__repr__", [](const seatmanager::Student& s) {
            return "<Student(id=" + std::to_string(s.getId()) + ", name='" + s.getName() + "')>";
        });
    
    py::class_<seatmanager::Seat>(m, "Seat")
        .def(py::init<>())
        .def(py::init<int, int, seatmanager::SeatType>(), py::arg("row"), py::arg("col"), py::arg("type") = seatmanager::SeatType::NORMAL)
        .def("getRow", &seatmanager::Seat::getRow)
        .def("setRow", &seatmanager::Seat::setRow)
        .def("getCol", &seatmanager::Seat::getCol)
        .def("setCol", &seatmanager::Seat::setCol)
        .def("getType", &seatmanager::Seat::getType)
        .def("setType", &seatmanager::Seat::setType)
        .def("isOccupied", &seatmanager::Seat::isOccupied)
        .def("setOccupied", &seatmanager::Seat::setOccupied)
        .def("getStudentId", &seatmanager::Seat::getStudentId)
        .def("setStudentId", &seatmanager::Seat::setStudentId)
        .def("toString", &seatmanager::Seat::toString)
        .def("__repr__", &seatmanager::Seat::toString);
    
    py::class_<seatmanager::Classroom, std::shared_ptr<seatmanager::Classroom>>(m, "Classroom")
        .def(py::init<>())
        .def(py::init<int, int, seatmanager::AisleLayout>(), py::arg("rows"), py::arg("cols"), py::arg("aisleLayout") = seatmanager::AisleLayout::NONE)
        .def("getRows", &seatmanager::Classroom::getRows)
        .def("setRows", &seatmanager::Classroom::setRows)
        .def("getCols", &seatmanager::Classroom::getCols)
        .def("setCols", &seatmanager::Classroom::setCols)
        .def("getAisleLayout", &seatmanager::Classroom::getAisleLayout)
        .def("setAisleLayout", &seatmanager::Classroom::setAisleLayout)
        .def("getCustomAisles", &seatmanager::Classroom::getCustomAisles)
        .def("setCustomAisles", &seatmanager::Classroom::setCustomAisles)
        .def("initializeSeats", &seatmanager::Classroom::initializeSeats)
        .def("addAisle", &seatmanager::Classroom::addAisle)
        .def("removeAisle", &seatmanager::Classroom::removeAisle)
        .def("getSeats", py::overload_cast<>(&seatmanager::Classroom::getSeats, py::const_))
        .def("getSeat", py::overload_cast<int, int>(&seatmanager::Classroom::getSeat, py::const_))
        .def("getTotalSeats", &seatmanager::Classroom::getTotalSeats)
        .def("getAvailableSeats", &seatmanager::Classroom::getAvailableSeats)
        .def("isValidPosition", &seatmanager::Classroom::isValidPosition)
        .def("clearAllAssignments", &seatmanager::Classroom::clearAllAssignments)
        .def("toString", &seatmanager::Classroom::toString)
        .def("__repr__", &seatmanager::Classroom::toString);
    
    py::class_<seatmanager::SeatManager>(m, "SeatManager")
        .def(py::init<>())
        .def("setClassroom", &seatmanager::SeatManager::setClassroom)
        .def("getClassroom", &seatmanager::SeatManager::getClassroom)
        .def("setStudents", &seatmanager::SeatManager::setStudents)
        .def("getStudents", &seatmanager::SeatManager::getStudents)
        .def("addStudent", &seatmanager::SeatManager::addStudent)
        .def("removeStudent", &seatmanager::SeatManager::removeStudent)
        .def("clearStudents", &seatmanager::SeatManager::clearStudents)
        .def("assignSeats", py::overload_cast<seatmanager::AssignmentAlgorithm>(&seatmanager::SeatManager::assignSeats))
        .def("assignSeatsCustom", &seatmanager::SeatManager::assignSeatsCustom)
        .def("assignStudentToSeat", &seatmanager::SeatManager::assignStudentToSeat)
        .def("moveStudent", &seatmanager::SeatManager::moveStudent)
        .def("swapSeats", &seatmanager::SeatManager::swapSeats)
        .def("removeStudentFromSeat", &seatmanager::SeatManager::removeStudentFromSeat)
        .def("getStudentAtSeat", &seatmanager::SeatManager::getStudentAtSeat, py::return_value_policy::reference)
        .def("getStudentSeatPositions", &seatmanager::SeatManager::getStudentSeatPositions)
        .def("validateAssignment", &seatmanager::SeatManager::validateAssignment)
        .def("clearAllAssignments", &seatmanager::SeatManager::clearAllAssignments)
        .def("shuffleStudents", &seatmanager::SeatManager::shuffleStudents)
        .def("sortStudentsByName", &seatmanager::SeatManager::sortStudentsByName)
        .def("sortStudentsById", &seatmanager::SeatManager::sortStudentsById)
        .def("exportToCSV", &seatmanager::SeatManager::exportToCSV)
        .def("importFromCSV", &seatmanager::SeatManager::importFromCSV)
        .def("exportToTXT", &seatmanager::SeatManager::exportToTXT)
        .def("importFromTXT", &seatmanager::SeatManager::importFromTXT)
        .def("exportToJSON", &seatmanager::SeatManager::exportToJSON)
        .def("importFromJSON", &seatmanager::SeatManager::importFromJSON)
        .def("generateSeatingReport", &seatmanager::SeatManager::generateSeatingReport);
}