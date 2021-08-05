#include <vector>
#include <iostream>
#include "mazeCell.h"

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED


class maze {

public:
   maze(int r, int c); // constructor

   // returns true if neigh is cell's neighbor
   //(i.e. in position left, right, top or bot
   // with respect to cell)
   bool neighbors(int cell, int neigh) const;

   // get rid of cell's wall between cell and neighbor
   // Note: this method should be invoked twice from the driver
   // code to smashWall(a,b) and to smashWall(b,a)
   void smashWall (int cell, int neigh);

   //print the maze
   void printMaze();

   // returns the number of rows in the maze
   int getRow() const {return row;}

   // returns the number of columns in the maze
   int getCol() const {return col;}

private:
    int row;
    int col;
    std::vector<mazeCell> theMaze;
};

#endif // MAZE_H_INCLUDED
