#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Seat.h"

namespace seatmanager {

enum class AisleLayout {
    NONE,
    CENTER,
    DUAL_SIDE,
    CUSTOM
};

class Classroom {
public:
    Classroom();
    Classroom(int rows, int cols, AisleLayout aisleLayout = AisleLayout::NONE);
    
    ~Classroom() = default;
    
    int getRows() const;
    void setRows(int rows);
    
    int getCols() const;
    void setCols(int cols);
    
    AisleLayout getAisleLayout() const;
    void setAisleLayout(AisleLayout layout);
    
    const std::vector<int>& getCustomAisles() const;
    void setCustomAisles(const std::vector<int>& aisles);
    
    void initializeSeats();
    void addAisle(int col);
    void removeAisle(int col);
    
    const std::vector<std::vector<Seat>>& getSeats() const;
    std::vector<std::vector<Seat>>& getSeats();
    
    Seat& getSeat(int row, int col);
    const Seat& getSeat(int row, int col) const;
    
    int getTotalSeats() const;
    int getAvailableSeats() const;
    
    bool isValidPosition(int row, int col) const;
    void clearAllAssignments();
    
    std::string toString() const;
    
private:
    int m_rows;
    int m_cols;
    AisleLayout m_aisleLayout;
    std::vector<int> m_customAisles;
    std::vector<std::vector<Seat>> m_seats;
};

}