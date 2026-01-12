#pragma once

#include <string>
#include <memory>

namespace seatmanager {

enum class SeatType {
    NORMAL,
    AISLE,
    EMPTY
};

class Seat {
public:
    Seat();
    Seat(int row, int col, SeatType type = SeatType::NORMAL);
    
    ~Seat() = default;
    
    int getRow() const;
    void setRow(int row);
    
    int getCol() const;
    void setCol(int col);
    
    SeatType getType() const;
    void setType(SeatType type);
    
    bool isOccupied() const;
    void setOccupied(bool occupied);
    
    int getStudentId() const;
    void setStudentId(int studentId);
    
    std::string toString() const;
    
private:
    int m_row;
    int m_col;
    SeatType m_type;
    bool m_occupied;
    int m_studentId;
};

}