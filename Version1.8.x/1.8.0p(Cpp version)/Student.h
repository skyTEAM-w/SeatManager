//
// Created by HW on 2022/2/15.
//

#ifndef INC_1_8_0P_CPP_VERSION__STUDENT_H
#define INC_1_8_0P_CPP_VERSION__STUDENT_H


#include <string>

using namespace std;

class Student {
private:
    string m_Name;
    int m_Id;

public:
    Student(const string &mName, int mId);

    virtual ~Student();

    const string &getMName() const;

    void setMName(const string &mName);

    int getMId() const;

    void setMId(int mId);
};


#endif //INC_1_8_0P_CPP_VERSION__STUDENT_H
