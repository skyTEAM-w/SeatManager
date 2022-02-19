//
// Created by HW on 2022/2/15.
//

#ifndef INC_1_8_0P_CPP_VERSION__SEATMANAGERIMP_H
#define INC_1_8_0P_CPP_VERSION__SEATMANAGERIMP_H

#include "fstream"
#include "vector"

class SeatManagerImp {
public:
    SeatManagerImp();

    virtual ~SeatManagerImp();

    static void showUI();
    void makeTable();

private:
    std::string File_Path;
    std::vector<std::string> SeatTableBuf;

};


#endif //INC_1_8_0P_CPP_VERSION__SEATMANAGERIMP_H
