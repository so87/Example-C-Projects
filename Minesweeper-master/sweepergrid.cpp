// Simon Owens
// CS 215: MP4
// SweeperGrid.cpp

#include "sweepergrid.h"
#include "sweepercell.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//default constructor
//defaults to col and row size 5, and bombs 25
SweeperGrid::SweeperGrid()
{
  AutoOpenCounter = 0;
  //initialize 2d array to col 5, row 5, and density 25
  numRows = 5;
  numColumns = 5;
  numBombs = 0;
  int density = 25;

  srand(time(0));
  grid = new SweeperCell[(numRows)*(numColumns)];
  
  //place bombs
  for(int r = 0; r < numRows; r++)
    for(int c = 0; c < numColumns; c++)
      {
	if(rand() % 100 + 1 < density)
	  {
	    PlaceBomb(r, c);
	  }
      }
 
}

//explicit value constructor
SweeperGrid::SweeperGrid(int initialRows, int initialCols, int density)
{
  AutoOpenCounter = 0;
  // make the grid
  grid = new SweeperCell[(initialRows)*(initialCols)];

  //asign data to private variables
  numRows = initialRows;
  numColumns = initialCols;
  numBombs = 0;

  //place bombs
  for(int r = 0; r < numRows; r++)
    for(int c = 0; c < numColumns; c++)
       {
	if(rand() % 100 + 1 < density)
	  {
	    PlaceBomb(r, c);
	  }
	
	}

  
}

//Function: At
// Determines where the row and col is at in this allocated array.
// Returns the location as a SweeperCell&
SweeperCell&
SweeperGrid::At(int row, int col) const 
{
  //throw out of range if row or col is not in grid
  if(row < 0 || row >= numRows || col < 0 || col >= numColumns)
    throw out_of_range("This location is invalid!");
  return grid[row * numColumns + col];
}

// Function GetRows
// Returns number or rows
int
SweeperGrid::GetRows() const
{
  return numRows;
}

// Function GetColumns
// Returns number of cols
int
SweeperGrid::GetColumns() const
{
  return numColumns;
}

// Function GetBombs
// Returns the number of bombs
int
SweeperGrid::GetBombs() const
{
  return numBombs;
}
// Function: GameWon
// If there are no more bombs then this returns true(game is won)
bool
SweeperGrid::GameWon() const
{
  if(numBombs == 0)  
    return true;
  else
    return false;
}

// Function: PlaceBomb
// Places a bomb at designated location. Returns nothing
void
SweeperGrid::PlaceBomb(int row, int col)
{
  //throw out of range if row or col is not in grid
  if(row < 0 || row > numRows || col < 0 || col > numColumns)
    throw out_of_range("This location is invalid!");
  //place bomb at location if there is one
  if(At(row, col).HasBomb() == false)
  {
  At(row, col).PlaceBomb();
  numBombs++;  

  //incriment the number of adjacent bombs of cell's neighbors
  for(int i = row-1; i < row+2; i++)
    for(int j = col-1; j < col+2; j++)
	{
	  if((i>=0)&&(j>=0)&&(i<numRows)&&(j<numColumns))
	    At(i,j).IncrementNumAdjacent();
 	}
  } 
}
// Function: Uncover
// Uncovers the cell, it is a bomb return true, else return false
bool
SweeperGrid::Uncover(int row, int col)
{
  //throw out of range if row or col is not in grid
  if(row < 0 || row > numRows || col < 0 || col > numColumns)
    throw out_of_range("This location is invalid!");
  
  // if there is no bomb, uncover and return true
  if((At(row, col).HasBomb() == false) && (At(row, col).IsCovered() == true))
    {
    At(row, col).Uncover();
    return false;
    }
  // if cell has already been uncovered
  else if (At(row, col).HasBomb() == false)
    return false;
  // else there is a bomb, return true
  else
   {
    At(row, col).Uncover();
    return true;
   }
  
  
}
// Function: Mark
// Marks the cell if it is not already marked
void
SweeperGrid::Mark(int row, int col)
{
  //throw out of range if row or col is not in grid
  if(row < 0 || row > numRows || col < 0 || col > numColumns)
    throw out_of_range("This location is invalid!");

  //check if cell is already marked
  if(At(row, col).IsMarked() == false)
   {
    // Mark the grid if it is in bounds
    At(row, col).Mark();
    if(At(row, col).HasBomb() == true)
      numBombs--;
   }
}
// Function: Unmark
// if the cell is marked then this function unmarks it
void
SweeperGrid::Unmark(int row, int col)
{
  //throw out of range if row or col is not in grid
  if(row < 0 || row > numRows || col < 0 || col > numColumns)
    throw out_of_range("This location is invalid!");

  //check if cell is already unmarked
  if(At(row, col).IsMarked() == true)
   {
    // unmark the grid if it is in bounds
    At(row, col).Unmark();
    if(At(row, col).HasBomb() == true)
     numBombs++;
   }
}
// Function: RemoveBomb
// This removes a bomb from a location and decrements the number of bombs.
// Also decrements the number of adjacent 
void
SweeperGrid::RemoveBomb(int row, int col)
{
  //throw out of range if row or col is not in grid
  if(row < 0 || row > numRows || col < 0 || col > numColumns)
    throw out_of_range("This location is invalid!");

  //remove the bomb from the location if there is one
  if(At(row, col).HasBomb() == true)
  {
  At(row, col).RemoveBomb();
  numBombs--;
	
 //decriment the number of adjacent bombs of cell's neighbors
  for(int i = row-1; i < row+2; i++)
    for(int j = col-1; j < col+2; j++)
	{
	  if((i>=0)&&(j>=0)&&(i<numRows)&&(j<numColumns))
	    At(i,j).DecrementNumAdjacent();
 	} 
  }
}


// Function: Write 
// This function writes the grid to an output stream and returns nothing
void
SweeperGrid::Write(ostream& out) const
{
  // write this grid into an ostream in rows and cols
  for(int j = 0; j < numRows; j++)
    {
      for(int i = 0; i < numColumns; i++)
	out << "  " << At(j, i);
      out << endl;
    }
  
}


// Big three

// Copy Constructor

SweeperGrid::SweeperGrid(const SweeperGrid& source)
{
  // make the new grid
  grid = new SweeperCell[source.numRows * source.numColumns];
  // find info about grid
  numRows = source.GetRows();
  numColumns = source.GetColumns();
  numBombs = source.GetBombs();
  // copy the grid over
  for(int r = 0; r < numRows; r++)
    for(int c = 0; c < numColumns; c++)
	grid[r*numColumns+c] = source.grid[r*numColumns+c];
}

// Destructor

SweeperGrid::~SweeperGrid()
{
  delete [] grid;
}

// Assignment Operator
void 
SweeperGrid::operator=(const SweeperGrid& source)
{
  //make the new grid if the sizes arent the same
  if((numRows != source.numRows) || (numColumns != source.numColumns))
    {
      delete [] grid;
    grid = new SweeperCell[source.GetRows() * source.GetColumns()];
    }
  //find out info about original grid
  numRows = source.GetRows();
  numColumns = source.GetColumns();
  numBombs =  source.GetBombs();
  //assign the old grid to the new grid
  for(int r = 0; r < numRows; r++)
    for(int c = 0; c < numColumns; c++)
	At(r, c) = source.At(r, c);
}



// extra credit
// Function: auto open 
void
SweeperGrid::AutoOpen(int row, int col)
{ 
  // make sure its in bounds
  if((row>=0)&&(col>=0)&&(row<numRows)&&(col<numColumns))  
  {
  //recursive step if number of adjacent is equal to zero
  if(At(row, col).GetNumAdjacent() == 0)
    {
      Uncover(row, col);
      if(AutoOpenCounter != 0)
      {
      
        //uncover the cell and the ones around it if they are inbounds
      if((row+1>=0)&&(col-1>=0)&&(row+1<numRows)&&(col-1<numColumns))
          Uncover(row+1, col-1);
      if((row+1>=0)&&(col+1>=0)&&(row+1<numRows)&&(col+1<numColumns))
          Uncover(row+1, col+1);
      if((row-1>=0)&&(col-1>=0)&&(row-1<numRows)&&(col-1<numColumns))
          Uncover(row-1, col-1);
      if((row-1>=0)&&(col+1>=0)&&(row-1<numRows)&&(col+1<numColumns))
          Uncover(row-1, col+1);
      if((row+1>=0)&&(col>=0)&&(row+1<numRows)&&(col<numColumns))
          Uncover(row+1, col);
      if((row-1>=0)&&(col>=0)&&(row-1<numRows)&&(col<numColumns))
          Uncover(row-1, col);
      if((row>=0)&&(col+1>=0)&&(row<numRows)&&(col+1<numColumns))
          Uncover(row, col+1);
      if((row>=0)&&(col-1>=0)&&(row<numRows)&&(col-1<numColumns))
          Uncover(row, col-1);
      }
      AutoOpenCounter++;
	//recursion for those around it
	if(At(row+1, col-1).IsCovered() == true)
          AutoOpen(row+1, col-1);
	if(At(row+1, col+1).IsCovered() == true)
          AutoOpen(row+1, col+1);
	if(At(row-1, col-1).IsCovered() == true)
          AutoOpen(row-1, col-1);
	if(At(row-1, col+1).IsCovered() == true)
          AutoOpen(row-1, col+1);
        if(At(row+1, col).IsCovered() == true)
	  AutoOpen(row+1, col);
	if(At(row-1, col-1).IsCovered() == true)
          AutoOpen(row-1, col);
	if(At(row, col+1).IsCovered() == true)
          AutoOpen(row, col+1);
	if(At(row, col-1).IsCovered() == true)
          AutoOpen(row, col-1);
	
    }
  }

}

void
SweeperGrid::FirstMove(int row, int col)
{
  //throw out of range if row or col is not in grid
  if(row < 0 || row >= numRows || col < 0 || col >= numColumns)
    throw out_of_range("This location is invalid!");
  bool bomb = true;
  while(bomb != false)
  {
  // generate a random column and row in bounds
  int newRow = rand() % numRows + 1;
  int newCol = rand() % numColumns + 1;
  // make sure it doesn't already have a bomb
  if(At(newRow, newCol).HasBomb() == false)
    {
    // if that new place doesn't have bomb, place a new one there, remove old
    PlaceBomb(newRow, newCol);
    RemoveBomb(row, col);
    bomb = false;
    }
  }
}
