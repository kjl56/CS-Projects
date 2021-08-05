#include "Employee.h"

Employee::Employee(int i, std::string n, int pay)
{
    identifier = i;
    lastname = n;
    salary = pay;
}

void Employee::print(std::ostream &out = std::cout)
{
    out << identifier << " " << lastname << " " << salary << ": ";
}



