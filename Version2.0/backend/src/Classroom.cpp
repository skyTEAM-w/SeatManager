#include "Classroom.h"
#include <sstream>
#include <stdexcept>

namespace seatmanager {

Classroom::Classroom()
    : m_rows(0)
    , m_cols(0)
    , m_aisleLayout(AisleLayout::NONE)
{
}

Classroom::Classroom(int rows, int cols, AisleLayout aisleLayout)
    : m_rows(rows)
    , m_cols(cols)
    , m_aisleLayout(aisleLayout)
{
    initializeSeats();
}

int Classroom::getRows() const {
    return m_rows;
}

void Classroom::setRows(int rows) {
    if (rows <= 0) {
        throw std::invalid_argument("Number of rows must be positive");
    }
    m_rows = rows;
    initializeSeats();
}

int Classroom::getCols() const {
    return m_cols;
}

void Classroom::setCols(int cols) {
    if (cols <= 0) {
        throw std::invalid_argument("Number of columns must be positive");
    }
    m_cols = cols;
    initializeSeats();
}

AisleLayout Classroom::getAisleLayout() const {
    return m_aisleLayout;
}

void Classroom::setAisleLayout(AisleLayout layout) {
    m_aisleLayout = layout;
    initializeSeats();
}

const std::vector<int>& Classroom::getCustomAisles() const {
    return m_customAisles;
}

void Classroom::setCustomAisles(const std::vector<int>& aisles) {
    m_customAisles = aisles;
    m_aisleLayout = AisleLayout::CUSTOM;
    initializeSeats();
}

void Classroom::initializeSeats() {
    m_seats.clear();
    m_seats.resize(m_rows);
    
    for (int row = 0; row < m_rows; ++row) {
        m_seats[row].resize(m_cols);
        for (int col = 0; col < m_cols; ++col) {
            SeatType type = SeatType::NORMAL;
            
            if (m_aisleLayout == AisleLayout::CENTER) {
                if (col == m_cols / 2) {
                    type = SeatType::AISLE;
                }
            } else if (m_aisleLayout == AisleLayout::DUAL_SIDE) {
                if (col == m_cols / 3 || col == (2 * m_cols) / 3) {
                    type = SeatType::AISLE;
                }
            } else if (m_aisleLayout == AisleLayout::CUSTOM) {
                for (int aisleCol : m_customAisles) {
                    if (col == aisleCol) {
                        type = SeatType::AISLE;
                        break;
                    }
                }
            }
            
            m_seats[row][col] = Seat(row, col, type);
        }
    }
}

void Classroom::addAisle(int col) {
    if (col >= 0 && col < m_cols) {
        m_seats[col].clear();
        for (int row = 0; row < m_rows; ++row) {
            m_seats[row][col].setType(SeatType::AISLE);
        }
    }
}

void Classroom::removeAisle(int col) {
    if (col >= 0 && col < m_cols) {
        for (int row = 0; row < m_rows; ++row) {
            m_seats[row][col].setType(SeatType::NORMAL);
        }
    }
}

const std::vector<std::vector<Seat>>& Classroom::getSeats() const {
    return m_seats;
}

std::vector<std::vector<Seat>>& Classroom::getSeats() {
    return m_seats;
}

Seat& Classroom::getSeat(int row, int col) {
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Invalid seat position");
    }
    return m_seats[row][col];
}

const Seat& Classroom::getSeat(int row, int col) const {
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Invalid seat position");
    }
    return m_seats[row][col];
}

int Classroom::getTotalSeats() const {
    int count = 0;
    for (const auto& row : m_seats) {
        for (const auto& seat : row) {
            if (seat.getType() == SeatType::NORMAL) {
                count++;
            }
        }
    }
    return count;
}

int Classroom::getAvailableSeats() const {
    int count = 0;
    for (const auto& row : m_seats) {
        for (const auto& seat : row) {
            if (seat.getType() == SeatType::NORMAL && !seat.isOccupied()) {
                count++;
            }
        }
    }
    return count;
}

bool Classroom::isValidPosition(int row, int col) const {
    return row >= 0 && row < m_rows && col >= 0 && col < m_cols;
}

void Classroom::clearAllAssignments() {
    for (auto& row : m_seats) {
        for (auto& seat : row) {
            seat.setOccupied(false);
            seat.setStudentId(-1);
        }
    }
}

std::string Classroom::toString() const {
    std::ostringstream oss;
    oss << "Classroom(" << m_rows << "x" << m_cols << ")";
    switch (m_aisleLayout) {
        case AisleLayout::NONE:
            oss << " NoAisles";
            break;
        case AisleLayout::CENTER:
            oss << " CenterAisle";
            break;
        case AisleLayout::DUAL_SIDE:
            oss << " DualSideAisles";
            break;
        case AisleLayout::CUSTOM:
            oss << " CustomAisles";
            break;
    }
    return oss.str();
}

}