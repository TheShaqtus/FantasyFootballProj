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



