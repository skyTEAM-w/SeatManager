#include "SeatManager.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <set>

namespace seatmanager {

SeatManager::SeatManager()
    : m_classroom(nullptr)
{
}

void SeatManager::setClassroom(std::shared_ptr<Classroom> classroom) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_classroom = classroom;
}

std::shared_ptr<Classroom> SeatManager::getClassroom() const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return m_classroom;
}

void SeatManager::setStudents(const std::vector<Student>& students) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_students = students;
}

const std::vector<Student>& SeatManager::getStudents() const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    return m_students;
}

void SeatManager::addStudent(const Student& student) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_students.push_back(student);
}

void SeatManager::removeStudent(int studentId) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_students.erase(
        std::remove_if(m_students.begin(), m_students.end(),
            [studentId](const Student& s) { return s.getId() == studentId; }),
        m_students.end()
    );
}

void SeatManager::clearStudents() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    m_students.clear();
}

void SeatManager::assignSeats(AssignmentAlgorithm algorithm) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_classroom) {
        throw std::runtime_error("Classroom not set");
    }
    
    clearAllAssignments();
    
    switch (algorithm) {
        case AssignmentAlgorithm::RANDOM:
            assignRandom();
            break;
        case AssignmentAlgorithm::ALPHABETICAL:
            assignAlphabetical();
            break;
        case AssignmentAlgorithm::ID_ORDER:
            assignByIdOrder();
            break;
        default:
            assignRandom();
            break;
    }
}

void SeatManager::assignSeatsCustom(const std::vector<int>& seatOrder) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_classroom) {
        throw std::runtime_error("Classroom not set");
    }
    
    clearAllAssignments();
    
    auto availableSeats = getAvailableSeatIndices();
    
    if (seatOrder.size() != m_students.size()) {
        throw std::invalid_argument("Seat order size must match student count");
    }
    
    for (size_t i = 0; i < m_students.size() && i < seatOrder.size(); ++i) {
        int seatIndex = seatOrder[i];
        if (seatIndex >= 0 && seatIndex < static_cast<int>(availableSeats.size())) {
            int flatIndex = availableSeats[seatIndex];
            int row = flatIndex / m_classroom->getCols();
            int col = flatIndex % m_classroom->getCols();
            assignStudentToSeat(m_students[i].getId(), row, col);
        }
    }
}

void SeatManager::assignStudentToSeat(int studentId, int row, int col) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_classroom || !m_classroom->isValidPosition(row, col)) {
        throw std::invalid_argument("Invalid seat position");
    }
    
    auto& seat = m_classroom->getSeat(row, col);
    if (seat.getType() != SeatType::NORMAL) {
        throw std::invalid_argument("Cannot assign to aisle or empty seat");
    }
    
    // Check if seat is already occupied by another student
    if (seat.isOccupied() && seat.getStudentId() != studentId) {
         // Optionally remove the other student from this seat in our records?
         // For now, we overwrite. But we should update m_seatAssignments for the evicted student.
         int evictedStudentId = seat.getStudentId();
         m_seatAssignments.erase(evictedStudentId);
    }

    seat.setStudentId(studentId);
    seat.setOccupied(true);
    
    m_seatAssignments[studentId] = {row, col};
}

void SeatManager::moveStudent(int studentId, int newRow, int newCol) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    auto it = m_seatAssignments.find(studentId);
    
    if (it != m_seatAssignments.end()) {
        int oldRow = it->second.first;
        int oldCol = it->second.second;
        if (m_classroom && m_classroom->isValidPosition(oldRow, oldCol)) {
            m_classroom->getSeat(oldRow, oldCol).setOccupied(false);
            m_classroom->getSeat(oldRow, oldCol).setStudentId(-1);
        }
    }
    
    assignStudentToSeat(studentId, newRow, newCol);
}

void SeatManager::swapSeats(int row1, int col1, int row2, int col2) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    
    if (!m_classroom) return;
    if (!m_classroom->isValidPosition(row1, col1) || !m_classroom->isValidPosition(row2, col2)) {
        throw std::invalid_argument("Invalid seat position");
    }
    
    auto& seat1 = m_classroom->getSeat(row1, col1);
    auto& seat2 = m_classroom->getSeat(row2, col2);
    
    if (seat1.getType() != SeatType::NORMAL || seat2.getType() != SeatType::NORMAL) {
        throw std::invalid_argument("Cannot swap with non-normal seats");
    }
    
    int studentId1 = seat1.isOccupied() ? seat1.getStudentId() : -1;
    int studentId2 = seat2.isOccupied() ? seat2.getStudentId() : -1;
    
    // Update Seat objects
    seat1.setStudentId(studentId2);
    seat1.setOccupied(studentId2 != -1);
    
    seat2.setStudentId(studentId1);
    seat2.setOccupied(studentId1 != -1);
    
    // Update Assignments map
    if (studentId1 != -1) {
        m_seatAssignments[studentId1] = {row2, col2};
    }
    if (studentId2 != -1) {
        m_seatAssignments[studentId2] = {row1, col1};
    }
}

void SeatManager::removeStudentFromSeat(int row, int col) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_classroom || !m_classroom->isValidPosition(row, col)) {
        return;
    }
    
    auto& seat = m_classroom->getSeat(row, col);
    int studentId = seat.getStudentId();
    
    if (studentId >= 0) {
        seat.setOccupied(false);
        seat.setStudentId(-1);
        
        m_seatAssignments.erase(studentId);
    }
}

const Student* SeatManager::getStudentAtSeat(int row, int col) const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_classroom || !m_classroom->isValidPosition(row, col)) {
        return nullptr;
    }
    
    const auto& seat = m_classroom->getSeat(row, col);
    int studentId = seat.getStudentId();
    
    if (studentId < 0) {
        return nullptr;
    }
    
    // Optimizing student lookup? 
    // m_students is vector. Still O(N).
    // Could add a map for students too if needed, but N is usually small.
    
    auto it = std::find_if(m_students.begin(), m_students.end(),
        [studentId](const Student& s) { return s.getId() == studentId; });
    
    return (it != m_students.end()) ? &(*it) : nullptr;
}

std::vector<std::pair<int, std::pair<int, int>>> SeatManager::getStudentSeatPositions() const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::vector<std::pair<int, std::pair<int, int>>> result;
    result.reserve(m_seatAssignments.size());
    for (const auto& entry : m_seatAssignments) {
        result.push_back(entry);
    }
    return result;
}

bool SeatManager::validateAssignment() const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (!m_classroom) {
        return false;
    }
    
    std::set<int> assignedSeats;
    std::set<int> assignedStudents;
    
    for (const auto& [studentId, pos] : m_seatAssignments) {
        int row = pos.first;
        int col = pos.second;
        
        if (!m_classroom->isValidPosition(row, col)) {
            return false;
        }
        
        const auto& seat = m_classroom->getSeat(row, col);
        if (seat.getType() != SeatType::NORMAL || !seat.isOccupied()) {
            return false;
        }
        
        if (seat.getStudentId() != studentId) {
            return false; 
        }

        int seatKey = row * m_classroom->getCols() + col;
        if (assignedSeats.count(seatKey) > 0) {
            return false;
        }
        assignedSeats.insert(seatKey);
        
        if (assignedStudents.count(studentId) > 0) {
            return false;
        }
        assignedStudents.insert(studentId);
    }
    
    return true;
}

void SeatManager::clearAllAssignments() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_classroom) {
        m_classroom->clearAllAssignments();
    }
    m_seatAssignments.clear();
}

void SeatManager::shuffleStudents() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_students.begin(), m_students.end(), g);
}

void SeatManager::sortStudentsByName() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::sort(m_students.begin(), m_students.end(),
        [](const Student& a, const Student& b) { return a.getName() < b.getName(); });
}

void SeatManager::sortStudentsById() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::sort(m_students.begin(), m_students.end(),
        [](const Student& a, const Student& b) { return a.getId() < b.getId(); });
}

void SeatManager::assignRandom() {
    // Already locked by assignSeats
    shuffleStudents();
    
    auto availableSeats = getAvailableSeatIndices();
    
    for (size_t i = 0; i < m_students.size() && i < availableSeats.size(); ++i) {
        int flatIndex = availableSeats[i];
        int row = flatIndex / m_classroom->getCols();
        int col = flatIndex % m_classroom->getCols();
        assignStudentToSeat(m_students[i].getId(), row, col);
    }
}

void SeatManager::assignAlphabetical() {
    // Already locked by assignSeats
    sortStudentsByName();
    
    auto availableSeats = getAvailableSeatIndices();
    
    for (size_t i = 0; i < m_students.size() && i < availableSeats.size(); ++i) {
        int flatIndex = availableSeats[i];
        int row = flatIndex / m_classroom->getCols();
        int col = flatIndex % m_classroom->getCols();
        assignStudentToSeat(m_students[i].getId(), row, col);
    }
}

void SeatManager::assignByIdOrder() {
    // Already locked by assignSeats
    sortStudentsById();
    
    auto availableSeats = getAvailableSeatIndices();
    
    for (size_t i = 0; i < m_students.size() && i < availableSeats.size(); ++i) {
        int flatIndex = availableSeats[i];
        int row = flatIndex / m_classroom->getCols();
        int col = flatIndex % m_classroom->getCols();
        assignStudentToSeat(m_students[i].getId(), row, col);
    }
}

std::vector<int> SeatManager::getAvailableSeatIndices() const {
    // Internal helper, expects lock to be held by caller or safe
    // But since it calls m_classroom->getSeats(), we should be careful.
    // If we lock recursively, we are fine.
    
    std::vector<int> indices;
    
    if (!m_classroom) {
        return indices;
    }
    
    const auto& seats = m_classroom->getSeats();
    
    for (int row = 0; row < m_classroom->getRows(); ++row) {
        for (int col = 0; col < m_classroom->getCols(); ++col) {
            if (seats[row][col].getType() == SeatType::NORMAL) {
                indices.push_back(row * m_classroom->getCols() + col);
            }
        }
    }
    
    return indices;
}

std::string SeatManager::exportToCSV(const std::string& filePath) const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::ofstream file(filePath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    
    file << "Student ID,Name,Gender,Class,Row,Column\n";
    
    for (const auto& [studentId, pos] : m_seatAssignments) {
        int row = pos.first;
        int col = pos.second;
        const Student* student = nullptr;
        
        for (const auto& s : m_students) {
            if (s.getId() == studentId) {
                student = &s;
                break;
            }
        }
        
        if (student) {
            file << student->getId() << ","
                 << student->getName() << ","
                 << student->getGender() << ","
                 << student->getClassName() << ","
                 << row << ","
                 << col << "\n";
        }
    }
    
    file.close();
    return "Exported to " + filePath;
}

bool SeatManager::importFromCSV(const std::string& filePath) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    std::getline(file, line);
    
    m_students.clear();
    clearAllAssignments();
    
    int studentId = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        
        std::string name, gender, className;
        int row, col;
        
        if (std::getline(iss, token, ',')) {
            try {
                studentId = std::stoi(token);
            } catch (...) {
                studentId++;
            }
        }
        
        std::getline(iss, name, ',');
        std::getline(iss, gender, ',');
        std::getline(iss, className, ',');
        
        if (std::getline(iss, token, ',')) {
            try {
                row = std::stoi(token);
            } catch (...) {
                continue;
            }
        }
        
        if (std::getline(iss, token, ',')) {
            try {
                col = std::stoi(token);
            } catch (...) {
                continue;
            }
        }
        
        Student student(name, studentId, gender, className);
        m_students.push_back(student);
        
        if (m_classroom && m_classroom->isValidPosition(row, col)) {
            assignStudentToSeat(studentId, row, col);
        }
    }
    
    file.close();
    return true;
}

std::string SeatManager::exportToTXT(const std::string& filePath) const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::ofstream file(filePath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    
    if (!m_classroom) {
        file << "No classroom configured\n";
        file.close();
        return "Exported to " + filePath;
    }
    
    const auto& seats = m_classroom->getSeats();
    
    for (int row = 0; row < m_classroom->getRows(); ++row) {
        for (int col = 0; col < m_classroom->getCols(); ++col) {
            const auto& seat = seats[row][col];
            
            if (seat.getType() == SeatType::AISLE) {
                file << "    ";
            } else if (seat.isOccupied()) {
                const Student* student = getStudentAtSeat(row, col);
                if (student) {
                    file << student->getName().substr(0, 4);
                    file << std::string(4 - std::min(4, (int)student->getName().length()), ' ');
                } else {
                    file << "    ";
                }
            } else {
                file << "----";
            }
            
            if (col < m_classroom->getCols() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }
    
    file.close();
    return "Exported to " + filePath;
}

bool SeatManager::importFromTXT(const std::string& filePath) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    int studentId = 0;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        
        int col = 0;
        while (iss >> token) {
            if (token != "----" && token != "    ") {
                Student student(token, studentId++);
                m_students.push_back(student);
                
                if (m_classroom) {
                    int row = static_cast<int>(m_students.size() - 1) / m_classroom->getCols();
                    if (m_classroom->isValidPosition(row, col)) {
                        assignStudentToSeat(student.getId(), row, col);
                    }
                }
            }
            col++;
        }
    }
    
    file.close();
    return true;
}

std::string SeatManager::exportToJSON(const std::string& filePath) const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::ofstream file(filePath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    
    file << "{\n";
    file << "  \"classroom\": {\n";
    
    if (m_classroom) {
        file << "    \"rows\": " << m_classroom->getRows() << ",\n";
        file << "    \"cols\": " << m_classroom->getCols() << ",\n";
        file << "    \"aisleLayout\": " << static_cast<int>(m_classroom->getAisleLayout()) << "\n";
    } else {
        file << "    \"rows\": 0,\n";
        file << "    \"cols\": 0,\n";
        file << "    \"aisleLayout\": 0\n";
    }
    
    file << "  },\n";
    file << "  \"students\": [\n";
    
    for (size_t i = 0; i < m_students.size(); ++i) {
        const auto& student = m_students[i];
        file << "    {\n";
        file << "      \"id\": " << student.getId() << ",\n";
        file << "      \"name\": \"" << student.getName() << "\",\n";
        file << "      \"gender\": \"" << student.getGender() << "\",\n";
        file << "      \"className\": \"" << student.getClassName() << "\"\n";
        file << "    }";
        
        if (i < m_students.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    
    file << "  ],\n";
    file << "  \"assignments\": [\n";
    
    int count = 0;
    for (auto it = m_seatAssignments.begin(); it != m_seatAssignments.end(); ++it) {
        const auto& [studentId, pos] = *it;
        int row = pos.first;
        int col = pos.second;
        file << "    {\n";
        file << "      \"studentId\": " << studentId << ",\n";
        file << "      \"row\": " << row << ",\n";
        file << "      \"col\": " << col << "\n";
        file << "    }";
        
        if (count < m_seatAssignments.size() - 1) {
            file << ",";
        }
        file << "\n";
        count++;
    }
    
    file << "  ]\n";
    file << "}\n";
    
    file.close();
    return "Exported to " + filePath;
}

bool SeatManager::importFromJSON(const std::string& filePath) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        return false;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    file.close();
    
    size_t pos = content.find("\"rows\":");
    if (pos != std::string::npos) {
        pos += 7;
        size_t endPos = content.find(",", pos);
        int rows = std::stoi(content.substr(pos, endPos - pos));
        
        pos = content.find("\"cols\":");
        if (pos != std::string::npos) {
            pos += 7;
            int cols = std::strtol(&content[pos], nullptr, 10);
            
            if (!m_classroom) {
                m_classroom = std::make_shared<Classroom>(rows, cols);
            } else {
                m_classroom->setRows(rows);
                m_classroom->setCols(cols);
            }
        }
    }
    
    pos = content.find("\"students\":");
    if (pos != std::string::npos) {
        m_students.clear();
        m_students.reserve(1000); // Pre-allocate some space
        
        size_t studentPos = content.find("\"id\":", pos);
        while (studentPos != std::string::npos) {
            studentPos += 6;
            int id = std::strtol(&content[studentPos], nullptr, 10);
            
            studentPos = content.find("\"name\":", studentPos);
            studentPos += 8;
            size_t endPos = content.find("\"", studentPos);
            std::string name = content.substr(studentPos, endPos - studentPos);
            
            studentPos = content.find("\"gender\":", studentPos);
            studentPos += 10;
            endPos = content.find("\"", studentPos);
            std::string gender = content.substr(studentPos, endPos - studentPos);
            
            studentPos = content.find("\"className\":", studentPos);
            studentPos += 13;
            endPos = content.find("\"", studentPos);
            std::string className = content.substr(studentPos, endPos - studentPos);
            
            Student student(name, id, gender, className);
            m_students.push_back(student);
            
            studentPos = content.find("\"id\":", studentPos);
            if (studentPos == std::string::npos || (content.find("\"assignments\":") != std::string::npos && studentPos > content.find("\"assignments\":"))) {
                break;
            }
        }
    }
    
    pos = content.find("\"assignments\":");
    if (pos != std::string::npos) {
        clearAllAssignments();
        
        size_t assignPos = content.find("\"studentId\":", pos);
        while (assignPos != std::string::npos) {
            assignPos += 13;
            int studentId = std::strtol(&content[assignPos], nullptr, 10);
            
            assignPos = content.find("\"row\":", assignPos);
            assignPos += 7;
            int row = std::strtol(&content[assignPos], nullptr, 10);
            
            assignPos = content.find("\"col\":", assignPos);
            assignPos += 7;
            int col = std::strtol(&content[assignPos], nullptr, 10);
            
            if (m_classroom && m_classroom->isValidPosition(row, col)) {
                assignStudentToSeat(studentId, row, col);
            }
            
            assignPos = content.find("\"studentId\":", assignPos);
        }
    }
    
    return true;
}

std::string SeatManager::generateSeatingReport() const {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    std::ostringstream oss;
    
    oss << "=== Seating Report ===\n\n";
    
    if (m_classroom) {
        oss << "Classroom: " << m_classroom->getRows() << "x" << m_classroom->getCols() << "\n";
        oss << "Total Seats: " << m_classroom->getTotalSeats() << "\n";
        oss << "Available Seats: " << m_classroom->getAvailableSeats() << "\n";
        oss << "Occupied Seats: " << m_seatAssignments.size() << "\n\n";
    } else {
        oss << "No classroom configured\n\n";
    }
    
    oss << "Students: " << m_students.size() << "\n\n";
    
    oss << "Seating Arrangement:\n";
    if (m_classroom) {
        const auto& seats = m_classroom->getSeats();
        
        for (int row = 0; row < m_classroom->getRows(); ++row) {
            oss << "Row " << (row + 1) << ": ";
            for (int col = 0; col < m_classroom->getCols(); ++col) {
                const auto& seat = seats[row][col];
                
                if (seat.getType() == SeatType::AISLE) {
                    oss << "[AISLE] ";
                } else if (seat.isOccupied()) {
                    const Student* student = getStudentAtSeat(row, col);
                    if (student) {
                        oss << "[" << student->getName() << "] ";
                    } else {
                        oss << "[?] ";
                    }
                } else {
                    oss << "[Empty] ";
                }
            }
            oss << "\n";
        }
    }
    
    return oss.str();
}

}
