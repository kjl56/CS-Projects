/*
COPYRIGHT (C) 2018 Kyle Lugo (4148313) All rights reserved.
Data Structures Project 4
Author.  Kyle Lugo
        kjl56@zips.uakron.edu
Version. 1.00 11.28.2018
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "DisjSets.h"
#include "maze.h"

//generates two distinct random integers in the range of [0, row * col);
//i.e. the random numbers should not be greater than maxN.
//These numbers represent random cells.
void twoRandom(int & n1, int & n2, int maxN )
{
  srand (time(NULL));
  n1 = rand() % maxN;
  n2 = rand() % maxN;
}

int main()
{
    int row = 0;
    int col = 0;

    std::cout << "Please enter the number of rows greater than 1: ";
    std::cin >> row;
    while (!std::cin || row < 2)
    {
      std::cout << "Please enter the number of rows greater than 1: ";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cin >> row;
    }

    std::cout << "Please enter the number of columns greater than 1: ";
    std::cin >> col;
    while (!std::cin || col < 2)
    {
      std::cout << "Please enter the number of columns greater than 1: ";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cin >> col;
    }

    bool notValid = true;
    char answer = ' ';
    do
    {
      std::cout << "Would you like to see each iteration of the maze?: ";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cin.get(answer);
      if (answer == 'y' || answer == 'n')
      {
        notValid = false;
      }
    } while (notValid);

    maze testMaze(row, col); //create maze
    testMaze.printMaze();

    int randCell1, randCell2;
    int maxN = row * col;

    DisjSets testSets(maxN); //create disjoint sets

    //loop until maze is done
    do
    {
      twoRandom(randCell1, randCell2, maxN);
      if (testMaze.neighbors(randCell1, randCell2)) //if the two random cells are neighbors
      {
        if (!testSets.isConnected(randCell1, randCell2)) //check if they are connected
        {
          //if not, smash the wall between them and union them so they are in the same set
          testMaze.smashWall(randCell1, randCell2);
          testMaze.smashWall(randCell2, randCell1);
          testSets.unionSets(testSets.find(randCell1), testSets.find(randCell2));
          //and then print current maze if user asked to do so
          if (answer == 'y')
          {
            std::cout << std::endl << "Neighbors " << randCell1 << ", " << randCell2 << " wall smashed below" << std::endl;
            testMaze.printMaze();
          }
        }
      }
    } while (!testSets.isConnected(0, maxN-1));

    if (answer == 'n')
    {
      testMaze.printMaze();
    }

    return 0;
}
