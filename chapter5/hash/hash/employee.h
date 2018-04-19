#pragma once
#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <string>
#include <iostream>

class Employee
{
public:
    Employee();
    Employee(const std::string &name, const std::string &address, const std::string &phoneNumber);
    Employee(const Employee &oth);
    Employee(Employee &&oth);
    ~Employee();
public:
    Employee &operator=(const Employee &oth);
    Employee &operator=(Employee &&oth);
    bool operator==(const Employee &oth) const;
    const std::string &getName(void) const;
    friend std::ostream &operator<<(std::ostream &out, const Employee &empl);

private:
    std::string name;
    std::string address;
    std::string phoneNumber;
};

#endif
