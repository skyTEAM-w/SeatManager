#include "Seat.h"
#include <sstream>

namespace seatmanager {

Seat::Seat()
    : m_row(0)
    , m_col(0)
    , m_type(SeatType::NORMAL)
    , m_occupied(false)
    , m_studentId(-1)
{
}

Seat::Seat(int row, int col, SeatType type)
    : m_row(row)
    , m_col(col)
    , m_type(type)
    , m_occupied(false)
    , m_studentId(-1)
{
}

int Seat::getRow() const {
    return m_row;
}

void Seat::setRow(int row) {
    m_row = row;
}

int Seat::getCol() const {
    return m_col;
}

void Seat::setCol(int col) {
    m_col = col;
}

SeatType Seat::getType() const {
    return m_type;
}

void Seat::setType(SeatType type) {
    m_type = type;
}

bool Seat::isOccupied() const {
    return m_occupied;
}

void Seat::setOccupied(bool occupied) {
    m_occupied = occupied;
}

int Seat::getStudentId() const {
    return m_studentId;
}

void Seat::setStudentId(int studentId) {
    m_studentId = studentId;
    m_occupied = (studentId >= 0);
}

std::string Seat::toString() const {
    std::ostringstream oss;
    oss << "Seat(" << m_row << "," << m_col << ")";
    if (m_type == SeatType::AISLE) {
        oss << "[AISLE]";
    } else if (m_type == SeatType::EMPTY) {
        oss << "[EMPTY]";
    } else if (m_occupied) {
        oss << "[Student:" << m_studentId << "]";
    }
    return oss.str();
}

}