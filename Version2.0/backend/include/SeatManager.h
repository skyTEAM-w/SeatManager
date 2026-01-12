#pragma once

#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <mutex>
#include <map>
#include "Student.h"
#include "Classroom.h"

namespace seatmanager {

enum class AssignmentAlgorithm {
    RANDOM,
    ALPHABETICAL,
    ID_ORDER,
    CUSTOM
};

class SeatManager {
public:
    SeatManager();
    ~SeatManager() = default;
    
    void setClassroom(std::shared_ptr<Classroom> classroom);
    std::shared_ptr<Classroom> getClassroom() const;
    
    void setStudents(const std::vector<Student>& students);
    const std::vector<Student>& getStudents() const;
    
    void addStudent(const Student& student);
    void removeStudent(int studentId);
    void clearStudents();
    
    void assignSeats(AssignmentAlgorithm algorithm = AssignmentAlgorithm::RANDOM);
    void assignSeatsCustom(const std::vector<int>& seatOrder);
    
    void assignStudentToSeat(int studentId, int row, int col);
    void moveStudent(int studentId, int newRow, int newCol);
    void swapSeats(int row1, int col1, int row2, int col2);
    void removeStudentFromSeat(int row, int col);
    
    const Student* getStudentAtSeat(int row, int col) const;
    std::vector<std::pair<int, std::pair<int, int>>> getStudentSeatPositions() const;
    
    bool validateAssignment() const;
    void clearAllAssignments();
    
    void shuffleStudents();
    void sortStudentsByName();
    void sortStudentsById();
    
    std::string exportToCSV(const std::string& filePath) const;
    bool importFromCSV(const std::string& filePath);
    
    std::string exportToTXT(const std::string& filePath) const;
    bool importFromTXT(const std::string& filePath);
    
    std::string exportToJSON(const std::string& filePath) const;
    bool importFromJSON(const std::string& filePath);
    
    std::string generateSeatingReport() const;
    
private:
    std::shared_ptr<Classroom> m_classroom;
    std::vector<Student> m_students;
    std::map<int, std::pair<int, int>> m_seatAssignments;
    mutable std::recursive_mutex m_mutex;
    
    void assignRandom();
    void assignAlphabetical();
    void assignByIdOrder();
    std::vector<int> getAvailableSeatIndices() const;
};

}