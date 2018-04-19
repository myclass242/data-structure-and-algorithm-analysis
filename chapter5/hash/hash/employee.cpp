#include "employee.h"



Employee::Employee()
    :name(std::string()), address(std::string()), phoneNumber(std::string())
{}

Employee::Employee(const std::string &name, const std::string &address, const std::string &phoneNumber)
    : name(name), address(address), phoneNumber(phoneNumber)
{}

Employee::Employee(const Employee & oth)
    :name(oth.name), address(oth.address), phoneNumber(oth.phoneNumber)
{
}

Employee::Employee(Employee && oth)
    :name(std::move(oth.name)), address(std::move(oth.address)), phoneNumber(std::move(oth.phoneNumber))
{
}

Employee::~Employee()
{
}

Employee & Employee::operator=(const Employee & oth)
{
    name = oth.name;
    address = oth.address;
    phoneNumber = oth.phoneNumber;
    return *this;
}

Employee &Employee::operator=(Employee && oth)
{
    name = std::move(oth.name);
    address = std::move(oth.address);
    phoneNumber = std::move(oth.phoneNumber);

    return *this;
}

bool Employee::operator==(const Employee & oth) const
{
    return name == oth.name && address == oth.address && phoneNumber == oth.phoneNumber;
}

const std::string &Employee::getName(void) const
{
    return name;
}

std::ostream & operator<<(std::ostream & out, const Employee & empl)
{
    out << "name: " << empl.name << ", " << "address: " << empl.address << ", " << "phone: " << empl.phoneNumber;
    return out;
}
