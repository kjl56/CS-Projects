//Author.  Kyle Lugo
//         kjl56@zips.uakron.edu
#include "Employee.h"
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <sstream>

//This function builds and returns a vector of employees using the Employee class file.
//You can prompt the user for the input file in this function.
//Give the user a nice error message if the input file does not exist and exit.
//Your code will output:
//Number of employees are: xxxxx
std::vector<Employee> employees()
{
  std::vector<Employee> empList;

  //prompt user for file name
  std::cout << "Enter file of employee data to process: ";
  std::string fileName;
  std::cin >> fileName;

  //check if file exists, if so load it. if not, print error
  std::ifstream inputFile;
  inputFile.open(fileName);
  if (inputFile)
  {//needs editing
    int numOfEmps = 0;
    while(!inputFile.eof())
    {
      int id, pay;
      std::string name;

      inputFile >> id;
      inputFile.get();
      std::getline(inputFile, name, '\t');
      inputFile >> pay;

      if (name != "")
      {
        Employee empTemp(id, name, pay);
        empList.push_back(empTemp);
        numOfEmps++;
        //std::cout << id << name << pay << std::endl;
      }
    }
    std::cout << "Number of employees are: " << numOfEmps << std::endl;
    return empList;
  }
  else
  {
    std::cout << "That file does not exist." << std::endl;
    Employee empTemp(0, " ", 0);
    empList.push_back(empTemp);
    return empList;
  }
}

//This function builds and returns an ordered map.
//The key for this map is the employee's department id.
//The department id is the first four most significant digits of the employee identifier.
//For example, a record in the records.dat file contains "882966 Etzel 120580" with 882966 as the employee id. The department this employee belongs to is 8829.
std::map<int,std::vector<Employee>> mapEmpDept(std::vector<Employee> & emp)
{
  std::map<int, std::vector<Employee>> empDeptOrdered;
  int lineNum = 0;

  while(lineNum != emp.size())
  {
    int department, tempNum;
    std::stringstream IDStream;
    std::string tempString, empName;

    //truncating employee id to obtain just the first 4 digits
    tempNum = emp[lineNum].id();
    IDStream << tempNum;
    for (int i = 0; i < 4; ++i)
    {
      tempString += IDStream.get();
    }
    std::istringstream (tempString) >> department;

    //inserting key and vector
    std::pair< std::map< int,std::vector<Employee> >::iterator,bool > mapIter;
    mapIter = empDeptOrdered.insert(std::pair<int, std::vector<Employee>>(department,emp));

    ++lineNum;
  }

  return empDeptOrdered;
}

//This function builds and returns an ordered map.
//The key for this map is related to the employee's salary based on 10,000 range increments.
//If the employee's salary is in the range of 40,000 to 49,999, the key is 40000.
//For example, a record in the records.dat file contains "882966 Etzel 120580" with 120580 as the employee's salary.
//The salary range for this employee is 120000. Thus, the range is in 10,000 increments.
//Range 0 takes values [0,10000) and the key for this is 0, range 10,000 takes values from [10000, 20000) and the key for this is 10000, ...
std::map<int,std::vector<Employee>> mapSalRange(std::vector<Employee> & emp)
{
  std::map<int,std::vector<Employee>> empSalRange;
  int lineNum = 0;
  while (lineNum != emp.size())
  {
    int salKey;
    salKey = emp[lineNum].sal()/10000;

    std::pair< std::map< int,std::vector<Employee> >::iterator,bool > mapIter;
    mapIter = empSalRange.insert(std::pair<int, std::vector<Employee>>(salKey,emp));

    ++lineNum;
  }
  return empSalRange;
}

//This function prints the number of employees within each range using an ordered map.
//Afterwards, it print the salary range with the most number of employees and prints the number of employees in this range.
//Example output produced by this function is:
//ORDERED Map Salary Range with most employees: 130000 containing 6400 employees.
void printSalRange(std::map<int,std::vector<Employee>> & salRange)
{

}

//This is identical to the mapEmpDept but returns an unordered_map.
std::unordered_map<int,std::vector<Employee>> umapEmpDept(std::vector<Employee> & emp)
{
  std::unordered_map<int, std::vector<Employee>> empDeptOrdered;
  int lineNum = 0;

  while(lineNum != emp.size())
  {
    int department, tempNum;
    std::stringstream IDStream;
    std::string tempString, empName;

    //truncating employee id to obtain just the first 4 digits
    tempNum = emp[lineNum].id();
    IDStream << tempNum;
    for (int i = 0; i < 4; ++i)
    {
      tempString += IDStream.get();
    }
    std::istringstream (tempString) >> department;

    //inserting key and vector
    std::pair< std::unordered_map< int,std::vector<Employee> >::iterator,bool > mapIter;
    mapIter = empDeptOrdered.insert(std::pair<int, std::vector<Employee>>(department,emp));

    ++lineNum;
  }

  return empDeptOrdered;
}

//This is identical to the umapSalRange but returns an unordered_map.
std::unordered_map<int,std::vector<Employee>> umapSalRange(std::vector<Employee> & emp)
{
  std::unordered_map<int,std::vector<Employee>> empSalRange;
  int lineNum = 0;
  while (lineNum != emp.size())
  {
    int salKey;
    salKey = emp[lineNum].sal()/10000;

    std::pair< std::unordered_map< int,std::vector<Employee> >::iterator,bool > mapIter;
    mapIter = empSalRange.insert(std::pair<int, std::vector<Employee>>(salKey,emp));

    ++lineNum;
  }
  return empSalRange;
}

//This is identical to the printSalRange but uses an unordered_map parameter.
void uprintSalRange(std::unordered_map<int,std::vector<Employee>> & salRange)
{

}
