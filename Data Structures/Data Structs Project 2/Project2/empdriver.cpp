/*
COPYRIGHT (C) 2018 Kyle Lugo (4148313) All rights reserved.
Data Structures Project II
Author.  Kyle Lugo
         kjl56@zips.uakron.edu
Version. 1.00 10.22.2018
*/
#include "empmaps.h"
#include "Employee.h"

#include <iostream>
#include <ctime>

int main()
{
  std::vector<Employee> empList;
  empList = employees();

  if (empList[0].id() != 0)
  {
    clock_t start, stop;

    start = clock ();
    std::map<int,std::vector<Employee>> empDeptOrdered;
    empDeptOrdered = mapEmpDept(empList);
    stop = clock ();
    std::cout << "ORDERED Map creation with department as key clock ticks: " << double(stop-start) << std::endl;
    std::cout << "ORDERED Map number of departments: " << empDeptOrdered.size() <<std::endl;

    start = clock ();
    std::map<int,std::vector<Employee>> empSalOrdered;
    empSalOrdered = mapSalRange(empList);
    stop = clock ();
    std::cout << "ORDERED Map creation with salary as key clock ticks: " << double(stop-start) << std::endl;
    std::cout << "ORDERED Map number of salary ranges: " << empSalOrdered.size() <<std::endl;

    printSalRange(empSalOrdered);

    start = clock ();
    std::unordered_map<int,std::vector<Employee>> empDeptUnordered;
    empDeptUnordered = umapEmpDept(empList);
    stop = clock ();
    std::cout << "UNORDERED Map creation with department as key clock ticks: " << double(stop-start) << std::endl;
    std::cout << "UNORDERED Map number of departments: " << empDeptOrdered.size() <<std::endl;

    start = clock ();
    std::unordered_map<int,std::vector<Employee>> empSalUnordered;
    empSalUnordered = umapSalRange(empList);
    stop = clock ();
    std::cout << "UNORDERED Map creation with salary as key clock ticks: " << double(stop-start) << std::endl;
    std::cout << "UNORDERED Map number of salary ranges: " << empSalOrdered.size() <<std::endl;

    uprintSalRange(empSalUnordered);
  }
  return 0;
}
