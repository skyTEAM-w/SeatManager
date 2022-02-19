//
// Created by HW on 2022/2/15.
//

#include "Student.h"

Student::~Student() {

}

Student::Student(const string &mName, int mId) : m_Name(mName), m_Id(mId) {
    this->m_Name = mName;
    this->m_Id = mId;
}

const string &Student::getMName() const {
    return m_Name;
}

void Student::setMName(const string &mName) {
    m_Name = mName;
}

int Student::getMId() const {
    return m_Id;
}

void Student::setMId(int mId) {
    m_Id = mId;
}
