// File: polynomial.tar          Instructor: Dr. Don Roberts
// Class: CS 215                 Date assigned:  October 14, 2015
// Assignment: MP4               Date completed: October 28, 2015
// Programmer: Simon Owens    
// This is a minesweeper program.  The user can input the size of the grid he 
//  he wants to play with and also the density percentage.  The user is then
//  propted to mark, unmark, or uncover a cell or quit.  The game is won by
//  marking all of the mines and uncovering the spaces that aren't mines.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "sweepergrid.h"
#include "sweepercell.h"

using namespace std;


int main(int argc, char* argv[])
{
  // Start of error checking
  if (argc != 4) { // number of arguements
    cerr << "Usage: " << argv[0] << " SRC DEST\n";
    return 1;
  }
  
  int rows = atoi(argv[1]);   // argv[1] is the name of rows
  if (rows < 5)
    {
      cerr << "Enter a row number greater than or equal to 5!\n";
      return 2;
    }
  int cols = atoi( argv[2] );   // argv[2] is the name of cols
  if (cols < 5)
    {
      cerr << "Enter a column number greater than or equal to 5!\n";
      return 2;
    }
  int densityOfBombs = atoi( argv[3] );   // argv[3] is the density
  if ((densityOfBombs < 25) || (densityOfBombs > 75))
    {
      cerr << "Enter a density between 25 and 75!\n";
      return 2;
    }
  // End of error checking

  // Construct the grid based off of persons entries
  SweeperGrid Grid(rows, cols, densityOfBombs);
  // Output the grid to the screen with the number of bombs
  int numBombs;
  numBombs = Grid.GetBombs();
  cout << "There are " << numBombs << " bombs in the grid." << endl << endl;
  Grid.Write(cout);
  
  int firstuncover = 0;
  bool won = false;
  char choice;
  // Make a loop that prompts user for command
  while(won == false)
  {
    // make a choice variable and grid location
    int rowChoice;
    int colChoice;
    
    try{
    // prompt user for choice
    cout << "Enter u to uncover, m to mark, k to unmark, q to quit: ";
    cin >> choice;
    }catch(const out_of_range & re)
	{cout << re.what() << "Please try again." << endl;}

    if(choice == 'q')
      break;

    // do different things based on u m or k
    if(choice == 'm')
	{
	 try
	 {
	 cout << endl << "Enter a location (row col) to mark: ";
    	 cin >> rowChoice >> colChoice;
    	 cout << endl;
	 Grid.Mark(rowChoice, colChoice);
	 }catch(const out_of_range & re)
	     {cout << re.what() << "Please try again." << endl;}

	}
    else if(choice == 'k')
	{
	 try
	 {
	 cout << endl << "Enter a location (row col) to unmark: ";
    	 cin >> rowChoice >> colChoice;
    	 cout << endl;
	 Grid.Unmark(rowChoice, colChoice);
	 }catch(const out_of_range & re)
	     {cout << re.what() << "Please try again." << endl;}

	}
    else if(choice == 'u')
	{
	 try
	 {
	 cout << endl << "Enter a location (row col) to uncover: ";
    	 cin >> rowChoice >> colChoice;
    	 cout << endl;
	 
	// if a bomb is uncovered break the loop because you lost
	// .GameWon is still false then
	if((Grid.Uncover(rowChoice, colChoice) == true) && (firstuncover ==  0))
	  {
	    Grid.FirstMove(rowChoice, colChoice);
	  }
        else if((Grid.Uncover(rowChoice, colChoice)==true)&&(firstuncover!=0))
	  {
	    Grid.Uncover(rowChoice, colChoice);
	    break;
	  }
	else 
	    Grid.Uncover(rowChoice, colChoice);
	 }catch(const out_of_range & re)
	     {cout << re.what() << "Please try again." << endl;}
	firstuncover++;
	//check for others to uncover extra credit
	//Grid.AutoOpen(rowChoice, colChoice);

	 
	}
    //If the number of bombs is zero the game is won
    if(numBombs == 0)
     {
      won = Grid.GameWon();
      break;
     }
    // output the new grid
    Grid.Write(cout);
  }//end of while loop

  //write what happens if user is a quiter
  if(choice == 'q')
   cout << "You are a quitter, and quitters never win. Have a bad day."<< endl;	


  // write what happens for if game is lost
  else if(Grid.GameWon() ==  false)
   {
    cout << "You've uncovered a mine!  Game over!!" << endl;
    // uncover all of the cells and display them
    for(int r = 0; r < rows; r++)
     for(int c = 0; c < cols; c++)
	Grid.Uncover(r, c);
    Grid.Write(cout);
   }
  // write what happens for if the game is won
  else
   {
    cout << "You've marked all of the bombs!  You've won!!" << endl;
    // uncover all of the cells and display them
    for(int r = 0; r < rows; r++)
      for(int c = 0; c < cols; c++)
	Grid.Uncover(r, c);
    Grid.Write(cout);
   }

  
  // end of game	
  return 0;
}



  

