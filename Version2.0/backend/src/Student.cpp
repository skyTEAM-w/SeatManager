#include "Student.h"
#include <algorithm>

namespace seatmanager {

Student::Student()
    : m_name("")
    , m_id(0)
    , m_gender("")
    , m_className("")
{
}

Student::Student(const std::string& name, int id)
    : m_name(name)
    , m_id(id)
    , m_gender("")
    , m_className("")
{
}

Student::Student(const std::string& name, int id, const std::string& gender, const std::string& className)
    : m_name(name)
    , m_id(id)
    , m_gender(gender)
    , m_className(className)
{
}

const std::string& Student::getName() const {
    return m_name;
}

void Student::setName(const std::string& name) {
    m_name = name;
}

int Student::getId() const {
    return m_id;
}

void Student::setId(int id) {
    m_id = id;
}

const std::string& Student::getGender() const {
    return m_gender;
}

void Student::setGender(const std::string& gender) {
    m_gender = gender;
}

const std::string& Student::getClassName() const {
    return m_className;
}

void Student::setClassName(const std::string& className) {
    m_className = className;
}

bool Student::operator==(const Student& other) const {
    return m_id == other.m_id;
}

bool Student::operator<(const Student& other) const {
    return m_name < other.m_name;
}

}