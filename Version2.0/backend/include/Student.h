#pragma once

#include <string>
#include <memory>

namespace seatmanager {

class Student {
public:
    Student();
    Student(const std::string& name, int id);
    Student(const std::string& name, int id, const std::string& gender, const std::string& className);
    
    ~Student() = default;
    
    const std::string& getName() const;
    void setName(const std::string& name);
    
    int getId() const;
    void setId(int id);
    
    const std::string& getGender() const;
    void setGender(const std::string& gender);
    
    const std::string& getClassName() const;
    void setClassName(const std::string& className);
    
    bool operator==(const Student& other) const;
    bool operator<(const Student& other) const;
    
private:
    std::string m_name;
    int m_id;
    std::string m_gender;
    std::string m_className;
};

}