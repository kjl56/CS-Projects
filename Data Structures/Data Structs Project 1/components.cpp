/*
COPYRIGHT (C) 2018 Kyle Lugo (4148313) All rights reserved.
Data Structures Project I
Author.  Kyle Lugo
        kjl56@zips.uakron.edu
Version. 1.00 10.01.2018
Purpose:
*/
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>

//declare adjacency list
std::vector <std::list<int>> adjlist;

//takes in an iterator to the beginning of a list and the end of the same list, along with an int to insert into the list
//assumes the list has at least one int already inside
//returns an iterator to the first node in the list that is greater than the value of the int being passed in
std::list<int>::iterator  find_gt(std::list<int>::iterator start, std::list<int>::iterator stop, int x)
{
  std::list<int>::iterator tempIter = start;
  bool foundPoint = false; //done so that search is stopped at first value found to be larger than the inserted int
  while (!foundPoint)
  {
    if (start == stop)
    {
      foundPoint = true;
      return start;
    }
    if (x < *start)
    {
      foundPoint = true;
      tempIter = start;
    }
    ++start;
  }
  return tempIter;
}

//gets file from user and opens it
//takes the numbers from the file and inserts them into the adjacency list in sorted order
//returns true if file was successfully opened, false otherwise
bool open_file()
{
  //prompt user for file name
  std::cout << "Please enter the graph filename to process: ";
  std::string fileName;
  std::cin >> fileName;

  //check if file exists, if so load it. if not, print error
  std::ifstream inputFile;
  inputFile.open(fileName);
  if (inputFile)
  {
    //take nums from file and put them into an adjacency list in sorted order
    std::string tempLine;
    int lineNum = 0; //line number of file
    while(!inputFile.eof())
    {
      std::list<int> makeList;
      adjlist.push_back(makeList);
      int numToInsert;
      //get first line from file, put it into a string
      std::getline(inputFile, tempLine);
      //store string into a string stream
      std::stringstream lineParse;
      lineParse << tempLine;
      //run loop until end of string stream
      while (!lineParse.eof())
      {
        //extract num by num from stream
        std::string tempNum;
        lineParse >> tempNum;
        //check to make sure is not a space
        if (std::stringstream(tempNum) >> numToInsert)
        {
          //put nums into adjacency list in sorted order, one at a time
          std::list<int>::iterator listBegin = adjlist[lineNum].begin();
          std::list<int>::iterator listEnd = adjlist[lineNum].end();

          if (listBegin == listEnd)
          {
            adjlist[lineNum].push_back(numToInsert);
          }
          else
          {
            std::list<int>::iterator listInsert = find_gt(listBegin, listEnd, numToInsert);
            adjlist[lineNum].insert(listInsert, numToInsert);
          }
        }
      }
      ++lineNum;
    }
  }
  else
  {
    std::cout << "That file does not exist." << std::endl;
    return false;
  }
  return true;
}

//displays the adjacency list
void display_adjList()
{
  int lineNum = 0;
  std::cout << "The adjacency list for your graph" << std::endl;

  std::vector<std::list<int>>::iterator vecStart = adjlist.begin();
  std::vector<std::list<int>>::iterator vecStop = adjlist.end();

  while (vecStart != vecStop)
  {
    std::list<int>::iterator listStart = adjlist[lineNum].begin();
    std::list<int>::iterator listStop = adjlist[lineNum].end();

    if (listStart != listStop)
    {
      std::cout << "list" << lineNum << " ";
    }
    while (listStart != listStop)
    {
      std::cout << *listStart << " ";
      ++listStart;
    }

    std::cout << std::endl;
    ++vecStart;
    ++lineNum;
  }
}

//should run in linear time
//takes in two references to two lists to compare
//assumes lists are sorted in ascending order and elements are unique
//returns a bool of true if two vertices belong to the same component and false otherwise
bool connComponent(const std::list<int> &L1, const std::list<int> &L2)
{
  //runs in O(n^2)
  for(auto i : L1)
  {
    for (auto j : L2)
    {
      if (i == j)
      {
        return true;
      }
    }
  }
  return false;
}

//merges two lists together if they belong to the same component and returns a bool of true if merged, otherwise returns false
//merges the smaller list into the larger list, leaving the smaller list to be empty
bool merge2(std::list<int> &L1, std::list<int> &L2)
{
  if (!connComponent(L1, L2))
  {
    return false;
  }

  if (L1.size() >= L2.size())
  {
    //merge L2 into L1
    while (L2.size() > 0)
    {
      std::list<int>::iterator listBegin = L1.begin();
      std::list<int>::iterator listEnd = L1.end();

      std::list<int>::iterator listInsert = find_gt(listBegin, listEnd, L2.front());
      L1.insert(listInsert, L2.front());
      L2.pop_front();
    }
    L1.unique();//deletes any duplicate values in the list
  }
  else
  {
    //merge L1 into L2
    while (L1.size() > 0)
    {
      std::list<int>::iterator listBegin = L2.begin();
      std::list<int>::iterator listEnd = L2.end();

      std::list<int>::iterator listInsert = find_gt(listBegin, listEnd, L1.front());
      L2.insert(listInsert, L1.front());
      L1.pop_front();
    }
    L2.unique();
  }
  return true;
}

//main function
int main()
{
  bool flag = open_file();
  if (flag)//file successfully opened
  {
    display_adjList();
    //prompt user for two lists
    //continue to prompt user for merges until there is just one list left or the user enters -1
    bool loop = true;
    do
    {
      std::cout << "Enter two list ids to potentially merge together or -1 to quit: ";
      int L1, L2;
      std::cin >> L1;
      if (L1 == -1)
      {
        return 0;
      }
      else
      {
        std::cin >> L2;
        if (L1 > adjlist.size() || L2 > adjlist.size() || L1 < -1 || L2 < 0)
        {
          std::cout << "Those are not valid lists." << std::endl;
        }
        else
        {
          //combine them if possible, state if they have been merged and display the list(s)
          std::list<int>& list1 = adjlist[L1];
          std::list<int>& list2 = adjlist[L2];
          bool merged = merge2(list1, list2);
          if (merged)
          {
            //if lists merged, the empty one needs to be deleted
            if (list2.size() == 0)//merged L2 into L1
            {
              adjlist.erase(adjlist.begin()+L2);
            }
            else//merged L1 into L2
            {
              adjlist.erase(adjlist.begin()+L1);
            }
            std::cout << "The lists are merged." << std::endl;
            display_adjList();
            if (adjlist.size() == 1)
            {
              std::cout << "No more lists to merge.";
              loop = false;
            }
          }
          else
          {
            std::cout << "The lists are not merged." << std::endl;
            display_adjList();
          }
        }
      }
    }while (loop);
  }
  return 0;
}
