//Simon Owens
//CS 215 MP4
//SweeperGrid.h
#ifndef	sweepergrid_H
#define sweepergrid_H

#include "sweepercell.h"
#include <stdexcept>
using namespace std;

class SweeperGrid {

 public:
  // constructors 
  SweeperGrid();
  SweeperGrid(int initialRows, int initialCols, int density);
  // Copy Constructor
  SweeperGrid(const SweeperGrid& source);    
  // Destructor 
  ~SweeperGrid();
  // accessors
  void Write(ostream& out) const;
  SweeperCell& At(int rows, int cols) const;
  int GetRows() const;
  int GetColumns() const;
  int GetBombs() const;
  bool GameWon() const;
  //operator
  void operator=(const SweeperGrid& source);
  
  // mutators
  void PlaceBomb(int row, int col);
  void RemoveBomb(int row, int col);
  bool Uncover(int row, int col);
  void Mark(int row, int col);
  void Unmark(int row, int col);
  void AutoOpen(int row, int col);
  void FirstMove(int row, int col);
 private:

  // variables
  int numRows;
  int numColumns;
  int numBombs;
  SweeperCell* grid;

  int AutoOpenCounter;

  // Operators:


};

#endif
