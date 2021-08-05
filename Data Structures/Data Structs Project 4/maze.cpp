//Kyle Lugo (4148313)
#include "maze.h"

//constructor
maze::maze(int r, int c)
{
  row = r;
  col = c;

  for (int i = 0; i < row; ++i)
  {
    for (int j = 0; j < col; ++j)
    {
      if (i == 0 && j == 0) //first cell is in top left corner and does not have a left wall or top wall
      {
        theMaze.push_back(mazeCell(false, true, false, true));
      }
      else if (i == row-1 && j == col-1) //last cell is in bottom right corner and does not have a right wall or a bottom wall
      {
        theMaze.push_back(mazeCell(true, false, true, false));
      }
      else
      {
        theMaze.push_back(mazeCell());
      }
    }
  }
}

// returns true if neigh is cell's neighbor (i.e. in position left, right, top or bot with respect to cell)
bool maze::neighbors(int cell, int neigh) const
{
  if ( (cell % col) == (neigh % col) ) //check to see if in same column
  {
    if ( ((cell / col) + 1) == (neigh / col) ) //check if cell is above neigh
    {
      return true;
    }
    else if ( (cell / col) == ((neigh / col) + 1) ) //check if cell is below neigh
    {
      return true;
    }
    else //they are in the same column but are not in adjacent rows
    {
      return false;
    }
  }
  else if ( (cell / col) == (neigh / col) ) //check to see if in same row
  {
    if ( ((cell % col) + 1) == (neigh % col) ) //check if cell is left of neigh
    {
      return true;
    }
    else if ( (cell % col) == ((neigh % col) + 1) ) //check if cell is right of neigh
    {
      return true;
    }
    else //they are in the same row but are not in adjacent columns
    {
      return false;
    }
  }
  else //they share neither a column nor row so they cannot possibly be neighbors
  {
    return false;
  }
}

// get rid of cell's wall between cell and neighbor
// assumes they are neighbors
void maze::smashWall(int cell, int neigh)
{
  if ( (cell % col) == (neigh % col) ) //check to see if in same column
  {
    if ( ((cell / col) + 1) == (neigh / col) ) //check if cell is above neigh
    {
      theMaze[cell].setBot(false);
    }
    else if ( (cell / col) == ((neigh / col) + 1) ) //check if cell is below neigh
    {
      theMaze[cell].setTop(false);
    }
  }
  else if ( (cell / col) == (neigh / col) ) //check to see if in same row
  {
    if ( ((cell % col) + 1) == (neigh % col) ) //check if cell is left of neigh
    {
      theMaze[cell].setRight(false);
    }
    else if ( (cell % col) == ((neigh % col) + 1) ) //check if cell is right of neigh
    {
      theMaze[cell].setLeft(false);
    }
  }
}

//print the maze
void maze::printMaze()
{
  //first print the top wall
  std::cout << "  ";
  for (int i = 1; i < col; ++i)
  {
    std::cout << " _";
  }
  std::cout << " " << std::endl;

  //print any rows after the first row
  for (int i = 1; i <= row; ++i)
  {
    for (int k = ((i - 1) * col); k < (i * col); ++k )
    {
      if (theMaze[k].getLeft()) //print left wall of each cell in ith row if it exists
      {
        std::cout << "|";
      }
      else
      {
        std::cout << " ";
      }
      if (theMaze[k].getBot()) //print bottom wall of each cell in ith row if it exists
      {
        std::cout << "_";
      }
      else
      {
        std::cout << " ";
      }
    }
    if (i != row)
    {
      std::cout << "|" << std::endl;
    }
    else
    {
      std::cout << " " << std::endl;
    }
  }
}
