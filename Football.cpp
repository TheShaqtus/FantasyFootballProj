#include <iostream>
#include "Football.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <stdlib.h> //allows atoi
#include <vector>
#include <iomanip>

using namespace std;

player* mergeRun(int input1, int input2, player* curr);
player* Merge(player* x, player* y, int input1, int input2);
player* listSplit(player* head);
player* insertionRun(player* head, int input1, int input2);
player* Insert(player* head, player* newEntry, int input1, int input2);

/*
Function Prototype:
Database::Database()

Function Description:
This is the constructor function. It intializes the Database by setting up the root node in the linked list.

Example:
Database* FFData = new Database();

Pre-Conditions:
To avoid memory issues, there must not already be an initialized Database.

Post-Conditions:
The root player node is created with placeholder values.
*/
Database::Database()
{
	// Creates new player node and sets the Database root to this node.
	player* temp = new player("", "", 1, "", 0);
	root = temp;
	temp->next = NULL;
}

/*
Function Prototype:
Database::~Database()

Function Description:
This is the destructor function. When called, it will clear out the Database by deleting each player node in the linked list, one at a time.

Example:
FFData->~Database();

Pre-Conditions:
A database must first be initialized for the function to be accessible.

Post-Conditions:
All data entries will be deleted and the root node will be replaced with blank place holder values.
*/
Database::~Database()
{

	// Set current node to first after the root.
	player* curr = root->next;
	// Clear out data in the root node and replace it with placeholder entries.
	root->name = "";
	root->team = "";
	root->games = 1;
	root->position = "";
	root->points = 0;
	root->avgPoints = 0.0;
	root->next = NULL;
	// Initialize node to be deleted.
	player* del;
	// Run until we reach the end of the list.
	while(curr!=NULL){
        // Set current node to next in the list.  Delete the previous node.
		del = curr;
		curr = curr->next;
		delete del;
	}
}

/*
Function Prototype:
void Database::buildDatabase(char*)

Function Description:
Opens "FantasyData.csv" and parses the file line be line. It creates new player nodes, places the parsed data into these nodes, and appends the nodes to the back of the linked list.

Example:
Database* FFData = new Database(); FFData->buildDatabase(argv[1]);

Pre-Conditions:
A database must first be initialized for the function to be accessible. The ProjectRun.cpp must be run with the command line argument of "FantasyData.csv".

Post-Conditions:
The linked list will be filled with the 200 data entries in the CSV and will start sorted by Points in Descending order. Root node pointer will remain the same.
*/
void Database::buildDatabase(char* fileName){

    // Initialize the file stream and incrementing variables
	ifstream myFile(fileName);
    string line;
    entryCount=0;
    player* temp = root;

    // Run until the end of the file is reached.
    while(getline(myFile, line)){

       // Find where each data field starts and ends in the line
       // Name, Team, Games Played, Position, Points
       // Converts Games Played and Points to integers with atoi
       int indexOfSpace=line.find(",");
       string name= line.substr(0, indexOfSpace);
       string secondline= line.substr(indexOfSpace+1);
       int indexOfSpace2=secondline.find(",");
       string team= secondline.substr(0, indexOfSpace2);
       string thirdline = secondline.substr(indexOfSpace2+1);
       int indexOfSpace3 = thirdline.find(",");
       string number= thirdline.substr(0, indexOfSpace3);
       int games= atoi(number.c_str());
       string fourthline= thirdline.substr(indexOfSpace3+1);
       int indexOfSpace4= fourthline.find(",");
       string position=fourthline.substr(0, indexOfSpace4);
       string points=fourthline.substr(indexOfSpace4+1);
       int playerpoints= atoi(points.c_str());

       // If we are at the root node, place all the data into the root.
       if(entryCount == 0){
           root->name = name;
           root->team = team;
           root->games= games;
           root->points= playerpoints;
           root->position= position;
           root->avgPoints= (playerpoints/(double)games);
       }
       // Else create a new player node, place the data into the node and append
       // it to the end of the linked list.
       else{
           player* n = new player;
           n->name = name;
           n->team = team;
           n->games= games;
           n->points= playerpoints;
           n->position= position;
           n->avgPoints= (playerpoints/(double)games);
           temp->next = n;
           temp = temp->next;
       }
       // Increase the entry count.
       entryCount++;
    }

    // Function complete!
    cout << "Database built." << endl;



}

/*
Function Prototype:
void Database::printDatabase()

Function Description:
Will start at the Database root node and iterate through the linked list, displaying each data entry in it's sorted order.

Example:
Database* FFData = new Database(); FFData->buildDatabase(argv[1]); FFData->printDatabase

Pre-Conditions:
The database must first be initialized and filled with the information in the CSV file with the buildDatabase function.

Post-Conditions:
Will display each database entry in the current sorted order and all data fields associated with that entry (Name, Team, Position, Games Played, Points, and Average Points.
*/
void Database::printDatabase(){

    // Start at Database root node
    player* curr = root;
    cout << "Name   Team   Position   Games Played   Points   Points/Game" << endl;
    // Run until we reach the end of the Database
    while(curr != NULL){
        // Display the current data entry and increment to the next node.
        cout << curr->name << "  " << curr->team << "  " << curr->position << "  " << curr->games << "  " << curr->points << "  " << fixed << setprecision(2) << curr->avgPoints  << endl;
        curr = curr->next;
    }
}

/*
Function Prototype:
void Database::comparePlayers(string, string)

Function Description:
Will search the database for 2 players based on their name. If a player is not found, it will display a message stating so. After each player is found, it will print both data entries on top of each other and calculate the difference in the games played, fantasy points scored, and average fantasy points scored.

Example:
getline(cin, in_string1);
getline(cin, in_string2);
FFData->comparePlayers(in_string1, in_string2);

Pre-Conditions:
The database must be intialized and filled using the buildDatabase function. Each input string is a user entered player name, which must match a database entry name and is case sensitive.

Post-Conditions:
Each player's stats will be displayed side by side with cout statements.
*/
void Database::comparePlayers(string name1, string name2){

    // Initialize variable placeholders and start at Database root
    player* curr = root;
    int count = 2;
    player* player1;
    player* player2;
    int gamesDel = 0;
    int pointsDel = 0;
    float avgPointsDel = 0;
    // Run until end of Database is reached.
    while(curr != NULL){
        // Check if current entry is one of the players we are looking for.
        if(curr->name.compare(name1) == 0){
            // Decrement the counter and set player1 to name1 player data.
            count--;
            player1 = curr;
        }else if(curr->name.compare(name2) == 0){
            // Decrement the counter and set player2 to name2 player data.
            count--;
            player2 = curr;
        }
        // Did we find both players?
        if(count == 0){
            break;
        }
        // Increment to next node in linked list.
        curr = curr->next;
    }
    // Were both players found?
    if(count != 0){
        cout << "Player(s) not found." << endl;
        return;
    }
    // Display the stats of each player next to each other and calculate the
    // difference between the 2 players.
    cout << "Name   Team   Position   Games Played   Points   Points/Game" << endl;
    cout << player1->name << "  " << player1->team << "  " << player1->position << "  " << player1->games << "  " << player1->points << "  " << player1->avgPoints << endl;
    cout << player2->name << "  " << player2->team << "  " << player2->position << "  " << player2->games << "  " << player2->points << "  " << player2->avgPoints << endl;
    gamesDel = player1->games - player2->games;
    pointsDel = player1->points - player2->points;
    avgPointsDel = player1->avgPoints - player2->avgPoints;
    cout << "Games Played Difference: " << gamesDel << endl;
    cout << "Fantasy Points Difference: " << pointsDel << endl;
    cout << "Average Fantasy Points Difference: " << avgPointsDel << endl;
}

/*
Function Prototype:
void Database::compareTeams(string, string)

Function Description:
Will search the database for all data entries with a user entered team abbreviation. It will then display each player's stats from the team as well as calculate the total team points and average points per player.

Example:
cout << "Enter Team 1 Abbreviation:" << endl;
getline(cin,in_string1);
cout << "Enter Team 2 Abbreviation:" << endl;
getline(cin,in_string2);
FFData->compareTeams(in_string1, in_string2);

Pre-Conditions:
Database must be intialized and filled using buildDatabase function. Each input string is a user entered team abbreviation, which must match a database entry abbreviation and is case sensitive.
List of Team Abbreviations: 2TM, ARI, ATL, BAL, BUF, CAR, CHI, CIN, CLE, DAL, DEN, DET, GNB, HOU, IND, JAX, KAN, MIA, MIN, NOR, NWE, NYG, NYJ, OAK, PHI, PIT, SDG, SEA, SFO, STL, TAM, TEN, WAS

Post-Conditions:
Each team's stats will be displayed, as well as each player found for the team with cout statements.
*/
void Database::compareTeams(string name1, string name2){

    /* Initialize the variables to hold all the players from each team, the total
    points of each team, total number of players from each team, and start at
    the Database root node.*/
    vector<player*> team1;
    vector<player*> team2;
    int points[2];
    points[0] = 0;
    points[1] = 0;
    int entries[2];
    entries[0] = 0;
    entries[1] = 0;
    player* curr = root;

    // Run until the end of the Database is reached.
    while(curr != NULL){
        // Check if current entry is on either team we are looking for.
        if(curr->team.compare(name1) == 0){
            // Add player to the end of the vector and add points to the team points.
            team1.push_back(curr);
            points[0] = points[0] + curr->points;
            entries[0]++;
        }else if(curr->team.compare(name2) == 0){
            team2.push_back(curr);
            points[1] = points[1] + curr->points;
            entries[1]++;
        }
        // Increment to next node in Database.
        curr = curr->next;
    }
    // Display stats of each player from team1.
    cout << "Player Stats of " << name1 << endl;
    for(int i = 0; i < team1.size(); i++){
        cout << team1[i]->name << "  " << team1[i]->position << "  " << team1[i]->games << "  " << team1[i]->points << "  " << fixed << setprecision(2) << team1[i]->avgPoints  << endl;
    }
    cout << "Total Team Points: " << points[0] << endl;
    cout << "Average Points per Player: " << fixed << setprecision(2) << points[0]/(double)entries[0] << endl;

    cout << " " << endl;
    // Display stats of each player from team2.
    cout << "Player Stats of " << name2 << endl;
    for(int i = 0; i < team2.size(); i++){
        cout << team2[i]->name << "  " << team2[i]->position << "  " << team2[i]->games << "  " << team2[i]->points << "  " << fixed << setprecision(2) << team2[i]->avgPoints  << endl;
    }
    cout << "Total Team Points: " << points[1] << endl;
    cout << "Average Points per Player: " << fixed << setprecision(2) << points[1]/(double)entries[1] << endl;
    cout << " " << endl;

}

/*
Function Prototype:
void Database::bubbleSort()

Function Description:
Uses a bubble sorting algorithm to sort the Database linked list by a data field of the user's choosing and either ascending or descending order. This sorting algorithm has an average complexity of O(n2).

Example:
FFData->buildDatabase(argv[1]);
FFData->bubbleSort();

Pre-Conditions:
The Database must be intialized and filled using the buildDatabase function. User inputs must be made for data field and sort order.

Post-Conditions:
Will update pointers of the linked list for the approriate sorting order and the root player node for the Database will be updated.
*/
void Database::bubbleSort(){

    // Initialize menu variables and temp nodes to increment through Database.
    int input1;
    int input2;
    player* curr = NULL;
    player* trail = NULL;
    player* temp = NULL;
    // Display user menu to chose data type to sort by
    cout << "==Choose Sort Field==" << endl;
    cout << "1. Player Name" << endl;
    cout << "2. Team" << endl;
    cout << "3. Position" << endl;
    cout << "4. Games Played" << endl;
    cout << "5. Points" << endl;
    cout << "6. Average Points" << endl;
    cin >> input1;
    cin.clear();
    cin.ignore(10000, '\n');
    // Display user menu to choose sort order.
    cout << "==Choose Sort Order==" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cin >> input2;

    // Switch statement for each data type case.
    switch(input1){

        // Sort by player name.
        case 1:
            // Check if Ascending or Descending
            if(input2 == 1){
                // Iterate for number of data entries in the Database
                for(int i = 0; i < entryCount; i++){
                    // Start at the Database root, increment until Database end is reached
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if current node's player name is alphabetically after the next one.
                        if(curr->name.compare(curr->next->name) > 0){
                            // Shift the current node to be after the next node.
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;
                            // If the current node is the root node, set the previous
                            // node and temp node to the root.
                            if(curr == root){
                                root = trail = temp;
                            // Otherwise, connect the previous node to the newly placed
                            // temp node.
                            }else{
                                trail->next = temp;
                            }
                            // Set the current node to the newly positioned node.
                            curr = temp;
                        }
                        // Increment the current and trailing nodes in the list.
                        trail = curr;
                        curr = curr->next;
                    }
                }
            // If descending, repeat same algorithm, but in opposite alphabetical order.
            }else if(input2 == 2){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if current node should be after the next node (reverse alphabetical)
                        if(curr->name.compare(curr->next->name) <= 0){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            }
            break;

        // Sort by team abbreviation
        case 2:
            // Ascending
            if(input2 == 1){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if current node team is the same or after the next alphabetically.
                        if(curr->team.compare(curr->next->team) >= 0){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            // Descending
            }else if(input2 == 2){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if current team is the same or after the next reverse alphabetically.
                        if(curr->team.compare(curr->next->team) <= 0){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            }
            break;

        // Sort by position
        case 3:
            // Ascending order
            if(input2 == 1){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check alphabetically
                        if(curr->position.compare(curr->next->position) >= 0){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            // Descending order
            }else if(input2 == 2){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check reverse alphabetically
                        if(curr->position.compare(curr->next->position) <= 0){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            }
            break;

        // Sort by games played
        case 4:
            // Ascending
            if(input2 == 1){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if numerical order
                        if(curr->games >= curr->next->games){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            // Descending
            }else if(input2 == 2){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if reverse numerical order
                        if(curr->games <= curr->next->games){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            }
            break;

        // Sort by points scored
        case 5:
            // Ascending
            if(input2 == 1){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if in mathematical order
                        if(curr->points >= curr->next->points){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            // Descending
            }else if(input2 == 2){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if reverse mathematical order
                        if(curr->points <= curr->next->points){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            }
            break;
        // Sort by average points scored
        case 6:
            // Ascending
            if(input2 == 1){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if in mathematical order
                        if(curr->avgPoints >= curr->next->avgPoints){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            // Descending
            }else if(input2 == 2){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        // Check if in reverse mathematical order
                        if(curr->avgPoints <= curr->next->avgPoints){
                            temp = curr->next;
                            curr->next = curr->next->next;
                            temp->next = curr;

                            if(curr == root){
                                root = trail = temp;
                            }else{
                                trail->next = temp;
                            }
                            curr = temp;
                        }
                        trail = curr;
                        curr = curr->next;
                    }
                }
            }
            break;



    }
    // Sort is finished!
    cout << "Sort complete." << endl;
}

/*
Function Prototype:
void Database::mergeSort()

Function Description:
Uses a merge sorting algorithm to sort the Database linked list by a data field of the user's choosing and either ascending or descending order. It completes this by calling the function player listSplit(player) which will split the Database into 2 separate linked lists. It will then call player mergeRun(int, int, player) and Merge(player, player, int, int) recursively, comparing each merging player node, adding to the linked list in proper order, and eventually update the Database root pointer. This algorithm has complexity of O(n log(n)).

Example:
FFData->buildDatabase(argv[1]);
FFData->mergeSort();

Pre-Conditions:
The Database must be intialized and filled using the buildDatabase function. User inputs must be made for data field and sort order.

Post-Conditions:
Will update pointers of the linked list for the approriate sorting order and the root player node for the Database will be updated.
*/
void Database::mergeSort(){

    // Initialize input variables and display user choice menu.
    int input1;
    int input2;
    cout << "==Choose Sort Field==" << endl;
    cout << "1. Player Name" << endl;
    cout << "2. Team" << endl;
    cout << "3. Position" << endl;
    cout << "4. Games Played" << endl;
    cout << "5. Points" << endl;
    cout << "6. Average Points" << endl;
    cin >> input1;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "==Choose Sort Order==" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cin >> input2;

    // Run the mergeRun function with the root node and 2 input values.
    // Update root node with the results of mergeRun
    root = mergeRun(input1, input2, root);
    cout << "Sort complete." << endl;

}

/*
Function Prototype:
void Database::insertionSort()

Function Description:
Uses a insertion sorting algorithm to sort the Database linked list by a data field of the user's choosing and either ascending or descending order. It completes this by calling the function insertionRun(player, int, int). insertionRun(player, int, int) will run the function Insert(player, player, int, int) for each node currently in the Database. The function Insert(player, player, int, int) will start at the root Database node and iterate through the Database until it finds the data entry that it is either larger or smaller than, and places itself before that entry. This algorithm has complexity of O(n2).

Example:
FFData->buildDatabase(argv[1]);
FFData->insertionSort();

Pre-Conditions:
The Database must be initialized and filled using the buildDatabase function. User inputs must be made for data field and sort order.

Post-Conditions:
Will update pointers of the linked list for the appropriate sorting order and the root player node for the Database will be updated.
*/
void Database::insertionSort(){
    // Initializes input variables and displays user menu.
    int input1;
    int input2;
    cout << "==Choose Sort Field==" << endl;
    cout << "1. Player Name" << endl;
    cout << "2. Team" << endl;
    cout << "3. Position" << endl;
    cout << "4. Games Played" << endl;
    cout << "5. Points" << endl;
    cout << "6. Average Points" << endl;
    cin >> input1;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "==Choose Sort Order==" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cin >> input2;
    // Calls the insertionRun function with the root node and input values.
    // Updates the root node with the sorting results.
    root = insertionRun(root, input1, input2);
    cout << "Sort complete." << endl;
}

/*
Function Prototype:
void Database::entrySelect(int, int);

Function Description:
Takes 2 user inputs for indexes (between 1 and 200), pull the player entries located at those positions in the Database, and display them together. It will also calculate the average points per player of the selection, the average games played, and average points per game.

Example:
FFData->buildDatabase(argv[1]);
cin >> index1;
cin >> index2;
FFData->entrySelect(index1, index2);

Pre-Conditions:
The Database must be intialized and filled using the buildDatabase function. The function takes in 2 integer variables between 1 and 200 that are inputted by the user.

Post-Conditions:
Will display the players from the starting index to the ending index with cout statements and calculate the average points per player, average games played, and average points per game of all players in the selection.
*/
void Database::entrySelect(int index1, int index2){

    // Initializes the head node to the root and tail node.
    player* head = root;
    player* tail = NULL;
    player* curr;
    // Calculate number of entries to be included in the selection
    int numEntries = index2-index1+1;
    // Initialize sums and average points.
    int pointSum = 0;
    int gameSum = 0;
    double avgPoints = 0.0;
    // Increment until we are at the first position
    for(int i = 1; i < index1; i++){
        head = head->next;
    }
    // Start at the first position and increment through linked list until we find the
    // second position.
    tail = head->next;
    for(int j = 0; j < index2-index1; j++){
        tail = tail->next;
    }
    // Set current node to head of the selection
    curr = head;
    // Increment until we reach the end position.
    while(curr->name.compare(tail->name) != 0){
        // Display the stats for each selection and calculate new sums.
        cout << curr->name << "  " << curr->team << "  " << curr->position << "  " << curr->games << "  " << curr->points << "  " << fixed << setprecision(2) << curr->avgPoints  << endl;
        pointSum = pointSum + curr->points;
        gameSum = gameSum +curr->games;
        curr = curr->next;

    }
    // Display the final sums and average points values of the selection
    avgPoints = pointSum / (double)gameSum;
    cout << "Average Points: " << fixed << setprecision(2) << pointSum/(double)numEntries << endl;
    cout << "Average Games Played: " << fixed << setprecision(2) << gameSum / (double)numEntries << endl;
    cout << "Average Points Per Game: " << fixed << setprecision(2) << avgPoints << endl;

}

/*
Function Prototype:
player* mergeRun(int, int, player*)

Function Description:
Will start with the root node of the Database and recursively split the Database into
halves until we are left with single nodes using the listSplit function.  It will
then run the Merge function for each node and return the head node of each newly
sorted list.

Example:
root = mergeRun(input1, input2, root);

Pre-Conditions:
Takes is the head node of a linked list as well as 2 user inputs to pass along to
the other functions.  The Database must be created and filled and the function should
called and replace the Database root node.

Post-Conditions:
Will recursively run until each node is merged together in the correctly sorted order.
Will return the new root node of the Database with updated pointers.
*/
player* mergeRun(int input1, int input2, player* head){
    // Check if the head node is a single node or NULL and return if so
    if(head == NULL || head->next == NULL){
        return head;
    }
    // Call listSplit function to find middle node of current linked list
    player* middle = listSplit(head);
    // Split the current list in half and update the pointers.
    player* secondHalf = middle->next;
    middle->next = NULL;
    // Call the Merge function recursively until all nodes have been iterated through
    // and merged together in the correct order.
    return Merge(mergeRun(input1, input2, head), mergeRun(input1, input2, secondHalf), input1, input2);

}

/*
Function Prototype:
player* listSplit(player*)

Function Description:
Starts at the head node of a linked list and will split it in half.  The player node
slow will be the middle node of the list.

Example:
player* middle = listSplit(head);

Pre-Conditions:
The mergeRun function must first be called.  It must take in a head node to a linked list.

Post-Conditions:
Will find the middle node of a list and return that node.
*/
player* listSplit(player* head){
    // Database is empty
    if(head == NULL){
        return head;
    }
    // Initialize incrementing nodes.
    player* slow = head;
    player* fast = head;
    // Increment until the fast node will reach the end of the list
    while(fast->next != NULL && fast->next->next != NULL){
        // Increment slow once and fast twice
        slow = slow->next;
        fast = fast->next->next;
    }
    // Return the middle node.
    return slow;
}

/*
Function Prototype:
player* Merge(player*, player*, int, int)

Function Description:
Will take the split lists and merge the nodes of each list together in the user
requested order by comparing each node and updating pointers for the nodes.

Example:
player* head = Merge(head, secondHalf, input1, input2);

Pre-Conditions:
Database must be initialized and filled.  In order for merge to work, it must take
in 2 head nodes of linked lists.  Each of these linked lists must be sorted to merge
correctly.

Post-Conditions:
Will merge the 2 input lists in sorted order and update the head node of the
now single list.  Pointers will be updated for the list and will return the head node.
*/
player* Merge(player* x, player* y, int input1, int input2){
    // Initialize nodes to iterate through the lists.
    player* temp = new player;
    // Place holder node for the front of the merged linked list
    player* curr = temp;
    // Check for data type to sort by
    switch(input1){

        // Sort by player name
        case 1:
            // Ascending order
            if(input2 == 1){
                // Run until we reach the end of one of the lists
                while(x != NULL && y != NULL){
                    // Check if x should be before or after y
                    if(x->name.compare(y->name) < 0){
                        // Set the next node to x and increment through the x list
                        curr->next = x;
                        x = x->next;
                    }else{
                        // Set the next node to y and increment through the y list
                        curr->next = y;
                        y = y->next;
                    }
                    // Increment to end of merged list
                    curr = curr->next;
                }
                // Have we reached the end of the x list
                if(x == NULL){
                    // Place the rest of the y list to the end of the merged list
                    curr->next = y;
                }else{
                    // Place the rest of the x list to the end of the merged list
                    curr->next = x;
                }
                // Merge has completed, new head node is first node after the
                // the placeholder node.
                return temp->next;
            // Descending order
            }else if(input2 == 2){
                // Repeat algorithm for opposite order
                while(x != NULL && y != NULL){
                    if(y->name.compare(x->name) > 0){
                        curr->next = y;
                        y = y->next;
                    }else{
                        curr->next = x;
                        x = x->next;
                    }
                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;
            }

        // Sort by team abbreviation
        case 2:
            // Ascending order
            if(input2 == 1){
                while(x != NULL && y != NULL){
                    if(x->team.compare(y->team) < 0){
                        curr->next = x;
                        x = x->next;
                    }else{
                        curr->next = y;
                        y = y->next;
                    }

                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;

            // Descending order
            }else if(input2 == 2){
                while(x != NULL && y != NULL){
                    if(y->team.compare(x->team) > 0){
                        curr->next = y;
                        y = y->next;
                    }else{
                        curr->next = x;
                        x = x->next;
                    }
                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;
            }

        // Sort by position
        case 3:
            // Ascending order
            if(input2 == 1){
                while(x != NULL && y != NULL){
                    if(x->position.compare(y->position) < 0){
                        curr->next = x;
                        x = x->next;
                    }else{
                        curr->next = y;
                        y = y->next;
                    }

                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;

            // Descending order
            }else if(input2 == 2){

                while(x != NULL && y != NULL){
                    if(y->position.compare(x->position) > 0){
                        curr->next = y;
                        y = y->next;
                    }else{
                        curr->next = x;
                        x = x->next;
                    }
                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;
            }

        // Sort by number of games played
        case 4:
            // Ascending order
            if(input2 == 1){
                while(x != NULL && y != NULL){
                    if(x->games <= y->games){
                        curr->next = x;
                        x = x->next;
                    }else{
                        curr->next = y;
                        y = y->next;
                    }

                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;

            // Descending order
            }else if(input2 == 2){

                while(x != NULL && y != NULL){
                    if(y->games >= x->games){
                        curr->next = y;
                        y = y->next;
                    }else{
                        curr->next = x;
                        x = x->next;
                    }
                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;
            }

        // Sort by points scored
        case 5:
            // Ascending order
            if(input2 == 1){
                while(x != NULL && y != NULL){
                    if(x->points <= y->points){
                        curr->next = x;
                        x = x->next;
                    }else{
                        curr->next = y;
                        y = y->next;
                    }

                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;

            // Descending order
            }else if(input2 == 2){
                while(x != NULL && y != NULL){
                    if(y->points >= x->points){
                        curr->next = y;
                        y = y->next;
                    }else{
                        curr->next = x;
                        x = x->next;
                    }
                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;
            }

        // Sort by average points per game
        case 6:
            // Ascending order
            if(input2 == 1){
                while(x != NULL && y != NULL){
                    if(x->avgPoints <= y->avgPoints){
                        curr->next = x;
                        x = x->next;
                    }else{
                        curr->next = y;
                        y = y->next;
                    }

                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;
            // Descending order
            }else if(input2 == 2){
                while(x != NULL && y != NULL){
                    if(y->avgPoints >= x->avgPoints){
                        curr->next = y;
                        y = y->next;
                    }else{
                        curr->next = x;
                        x = x->next;
                    }
                    curr = curr->next;
                }
                if(x == NULL){
                    curr->next = y;
                }else{
                    curr->next = x;
                }
                return temp->next;
            }

    }
    // return statement to prevent function from reaching end of non void function
    return temp->next;
}

/*
Function Prototype:
player* insertionRun(player*, int, int)

Function Description:

*/
player* insertionRun(player* head, int input1, int input2){
    if(head == NULL || head->next == NULL){
        return head;
    }
    player* curr = head->next;
    player* result = head;
    result->next = NULL;
    while(curr != NULL){
        player* temp = curr;
        curr = curr->next;
        result = Insert(result, temp, input1, input2);
    }
    return result;
}

player* Insert(player* head, player* newEntry, int input1, int input2){

    switch(input1){
        case 1:
            if(input2 == 1){
                if(head == NULL || head->name.compare(newEntry->name) > 0){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->name.compare(newEntry->name) < 0){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }else if(input2 == 2){
                if(head == NULL || head->name.compare(newEntry->name) < 0){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->name.compare(newEntry->name) > 0){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }

        case 2:
            if(input2 == 1){
                if(head == NULL || head->team.compare(newEntry->team) >= 0){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->team.compare(newEntry->team) < 0){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }else if(input2 == 2){
                if(head == NULL || head->team.compare(newEntry->team) <= 0){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->team.compare(newEntry->team) > 0){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }

        case 3:
            if(input2 == 1){
                if(head == NULL || head->position.compare(newEntry->position) >= 0){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->position.compare(newEntry->position) < 0){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }else if(input2 == 2){
                if(head == NULL || head->position.compare(newEntry->position) <= 0){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->position.compare(newEntry->position) > 0){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }

        case 4:
            if(input2 == 1){
                if(head == NULL || head->games >= newEntry->games){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->games < newEntry->games){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }else if(input2 == 2){
                if(head == NULL || head->games <= newEntry->games){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->games > newEntry->games){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }

        case 5:
            if(input2 == 1){
                if(head == NULL || head->points >= newEntry->points){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->points < newEntry->points){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }else if(input2 == 2){
                if(head == NULL || head->points <= newEntry->points){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->points > newEntry->points){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }

        case 6:
            if(input2 == 1){
                if(head == NULL || head->avgPoints >= newEntry->avgPoints){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->avgPoints < newEntry->avgPoints){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }else if(input2 == 2){
                if(head == NULL || head->avgPoints <= newEntry->avgPoints){
                    newEntry->next = head;
                    head = newEntry;
                    return head;
                }
                player* curr = head;
                player* prev = NULL;
                while(curr != NULL && curr->avgPoints > newEntry->avgPoints){
                    prev = curr;
                    curr = curr->next;
                }
                newEntry->next = curr;
                prev->next = newEntry;
                return head;
            }
    }
    return head;
}
