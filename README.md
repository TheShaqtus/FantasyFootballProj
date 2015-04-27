# Fantasy Football Project
CSCI 2270 Final Project

**Summary**

This project will use an extensive list of Fantasy Football data online in CSV format.  it will read the data from the file into a database controlled by a linked list.  The program will allow for a number of functions to analyze the data, much like SQL query functions.  The functions included in the program are:
* Build - this function will read the data file and build multiple doubly linked list, one for each position (QB, RB, WR, TE) and 1 for all players.  The CSV file is sorted by Fantasy Points in descending order.
* Sort - this function will allow the user to select a data type to sort by (Name, Team, Games Played, Position, Points, Points/Game) and select an order to sort by (Ascending/Descending). It also contains 3 methods of sorting: Bubble Sort, Merge Sort, and Insertion Sort.
* Search - This function will allow the user to search a data type for a result and will print out that result.
* Compare Players- Will allow the user to compare multiple players stats.
* Compare Teams - Will pull all players of each team in the database and compare them.
* Print - Will display the information in the database in it's currently sorted state.
* Select - Will allow the user to input 2 indexes of the database and will display the data for the entries in those indexes.

**How To Run**

* Download the files ProjectRun.cpp, Football.cpp, Football.h, and FantasyData.csv.
* Place all 4 files into the same folder and build the files together.
* Run ProjectRun.cpp with command line argument "FantasyData.csv".
* The program menu will appear.  To run most functions, you must first run the "Build Database" function by entering 1.
* Project Documentation can be found [here](https://github.com/TheShaqtus/FantasyFootballProj/edit/master/README.md).

**Dependencies**

No dependencies besides provided data are necessary.

**System Requirements**

Program will be developed in Linux environment, so for best results, please run in the same environment.

**Group Members**

Adam Mraz  
Edward Wassman

**Contributors**

None :(

**Open Issues/Bugs**

No code yet!

