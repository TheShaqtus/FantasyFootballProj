# Project Documentation

**Database**

Function Prototype:  
Database::Database()

Function Description:  
This is the constructor function.  It intializes the Database by setting up the root node in the linked list.

Example:  
Database* FFData = new Database();

Pre-Conditions:  
To avoid memory issues, there must not already be an initialized Database.

Post-Conditions:  
The root player node is created with placeholder values.

**~Database**

Function Prototype:  
Database::~Database()

Function Description:  
This is the destructor function.  When called, it will clear out the Database by deleting each player node in the linked list, one at a time.

Example:  
FFData->~Database();

Pre-Conditions:  
A database must first be initialized for the function to be accessible.

Post-Conditions:  
All data entries will be deleted and the root node will be replaced with blank place holder values.


**buildDatabase**

Function Prototype:
void Database::buildDatabase(char*)

Function Description:  
Opens "FantasyData.csv" and parses the file line be line.  It creates new player nodes, places the parsed data into these nodes, and appends the nodes to the back of the linked list.

Example:  
Database* FFData = new Database();
FFData->buildDatabase(argv[1]);

Pre-Conditions:  
A database must first be initialized for the function to be accessible.  The ProjectRun.cpp must be run with the command line argument of "FantasyData.csv".

Post-Conditions:  
The linked list will be filled with the 200 data entries in the CSV and will start sorted by Points in Descending order.  Root node pointer will remain the same.

**printDatabase**

Function Prototype:  
void Database::printDatabase()

Function Description:  
Will start at the Database root node and iterate through the linked list, displaying each data entry in it's sorted order.

Example:  
Database* FFData = new Database();
FFData->buildDatabase(argv[1]);
FFData->printDatabase

Pre-Conditions:  
The database must first be initialized and filled with the information in the CSV file with the buildDatabase function.

Post-Conditions:  
Will display each database entry in the current sorted order and all data fields associated with that entry (Name, Team, Position, Games Played, Points, and Average Points.

**comparePlayers**

Function Prototype:  
void Database::comparePlayers(string, string)

Function Description:  
Will search the database for 2 players based on their name.  If a player is not found, it will display a message stating so.  After each player is found, it will print both data entries on top of each other and calculate the difference in the games played, fantasy points scored, and average fantasy points scored.

Example:  
getline(cin, in_string1);
getline(cin, in_string2);
FFData->comparePlayers(in_string1, in_string2);

Pre-Conditions:  
The database must be intialized and filled using the buildDatabase function.  Each input string is a user entered player name, which must match a database entry name and is case sensitive.

Post-Conditions:  
Each player's stats will be displayed side by side with cout statements.

**compareTeams**

Function Prototype:  
void Database::compareTeams(string, string)

Function Description:  
Will search the database for all data entries with a user entered team abbreviation.  It will then display each player's stats from the team as well as calculate the total team points and average points per player.

Example:  
cout << "Enter Team 1 Abbreviation:" << endl;
getline(cin,in_string1);
cout << "Enter Team 2 Abbreviation:" << endl;
getline(cin,in_string2);
FFData->compareTeams(in_string1, in_string2);

Pre-Conditions:  
Database must be intialized and filled using buildDatabase function.  Each input string is a user entered team abbreviation, which must match a database entry abbreviation and is case sensitive.  
List of Team Abbreviations: 2TM, ARI, ATL, BAL, BUF, CAR, CHI, CIN, CLE, DAL, DEN, DET, GNB, HOU, IND, JAX, KAN, MIA, MIN, NOR, NWE, NYG, NYJ, OAK, PHI, PIT, SDG, SEA, SFO, STL, TAM, TEN, WAS

Post-Conditions:  
Each team's stats will be displayed, as well as each player found for the team with cout statements.

**bubbleSort**

Function Prototype:  
void Database::bubbleSort()

Function Description:  
Uses a bubble sorting algorithm to sort the Database linked list by a data field of the user's choosing and either ascending or descending order.  This sorting algorithm has an average complexity of O(n<sup>2</sup>).

Example:  
FFData->buildDatabase(argv[1]);
FFData->bubbleSort();

Pre-Conditions:  
The Database must be intialized and filled using the buildDatabase function.  User inputs must be made for data field and sort order.

Post-Conditions:  
Will update pointers of the linked list for the approriate sorting order and the root player node for the Database will be updated.

**mergeSort**

Function Prototype:  
void Database::mergeSort()

Function Description:  
Uses a merge sorting algorithm to sort the Database linked list by a data field of the user's choosing and either ascending or descending order.  It completes this by calling the function player listSplit(player) which will split the Database into 2 separate linked lists.  It will then call player mergeRun(int, int, player) and Merge(player, player, int, int) recursively, comparing each merging player node, adding to the linked list in proper order, and eventually update the Database root pointer.  This algorithm has complexity of O(n log(n)).

Example:  
FFData->buildDatabase(argv[1]);
FFData->mergeSort();

Pre-Conditions:  
The Database must be intialized and filled using the buildDatabase function.  User inputs must be made for data field and sort order.

Post-Conditions:  
Will update pointers of the linked list for the approriate sorting order and the root player node for the Database will be updated.

**insertionSort**

Function Prototype:  
void Database::insertionSort()

Function Description:  
Uses a insertion sorting algorithm to sort the Database linked list by a data field of the user's choosing and either ascending or descending order.  It completes this by calling the function insertionRun(player, int, int).  insertionRun(player, int, int) will run the function Insert(player, player, int, int) for each node currently in the Database.  The function Insert(player, player, int, int) will start at the root Database node and iterate through the Database until it finds the data entry that it is either larger or smaller than, and places itself before that entry.  This algorithm has complexity of O(n<sup>2</sup>).

Example:  
FFData->buildDatabase(argv[1]);
FFData->insertionSort();

Pre-Conditions:  
The Database must be intitialized and filled using the buildDatabase function.  User inputs must be made for data field and sort order.

Post-Conditions:  
Will update pointers of the linked list for the approriate sorting order and the root player node for the Database will be updated.

**entrySelect**

Function Prototype:  
void Database::entrySelect(int, int);

Function Description:  
Takes 2 user inputs for indexes (between 1 and 200), pull the player entries located at those positions in the Database, and display them together.  It will also calculate the average points per player of the selection, the average games played, and average points per game.

Example:  
FFData->buildDatabase(argv[1]);
cin >> index1;
cin >> index2;
FFData->entrySelect(index1, index2);

Pre-Conditions:  
The Database must be intialized and filled using the buildDatabase function.  The function takes in 2 integer variables between 1 and 200 that are inputted by the user.

Post-Conditions:  
Will display the players from the starting index to the ending index with cout statements and calculate the average points per player, average games played, and average points per game of all players in the selection.
