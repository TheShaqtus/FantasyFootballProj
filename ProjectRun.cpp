##include <iostream>
#include "Football.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <stdlib.h> //allows atoi
#include <vector>

using namespace std;

// Main running function, takes in command line arguments.
int main(int argc, char* argv[]){

    /* Initialize variables to work Main Menu selection, sort selection, team/player
    comparisons.  Also initializes the database.*/
	int input;
	int sort;
	int index1, index2;
	string in_string1;
	string in_string2;
	// Calls the Database constructor function.
	Database* FFData = new Database();
	bool quit = false;

    // Run until the quit option is chosen.
	while(quit != true){

		cout << "====MENU====" << endl;
		cout << "1. Build Database" << endl;
		cout << "2. Print Database" << endl;
		cout << "3. Sort Database" << endl;
		cout << "4. Compare Players" << endl;
		cout << "5. Compare Teams" << endl;
		cout << "6. Select Database Entries" << endl;
		cout << "7. Delete Database" << endl;
		cout << "8. Quit" << endl;

        // Get Main Menu input.
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');

		switch(input){

			case 1:
			    // Call buildDatabase public function to fill the database from
			    // the "FantasyData.csv" file.
				FFData->buildDatabase(argv[1]);
				break;

			case 2:
			    // Call printDatabase public function to display the current database.
				FFData->printDatabase();
				break;

			case 3:
			    // Display menu for user to select the sorting method.
				cout << "==Choose Sort Method==" << endl;
				cout << "1. Bubble Sort" << endl;
				cout << "2. Insertion Sort" << endl;
				cout << "3. Merge Sort" << endl;
				cin >> sort;
				if(sort == 1){
                    // Call the bubbleSort public function.
					FFData->bubbleSort();
					break;
				}else if(sort == 2){
				    // Call the insertionSort public function.
					FFData->insertionSort();
					break;
				}else if(sort == 3){
				    // Call the mergeSort public function.
					FFData->mergeSort();
					break;
				}else{
				    // User input was not 1, 2, or 3 and is not a valid option.
					cout << "Not a valid choice." << endl;
				}

			case 4:
			    /* Ask user to input 2 player names (spelling and case must be correct)
			    Then calls the comparePlayers public function with these 2 user inputs.*/
				cout << "Enter Player 1 Name:" << endl;
				getline(cin,in_string1);
				cout << "Enter Player 2 Name:" << endl;
				getline(cin,in_string2);
				FFData->comparePlayers(in_string1, in_string2);
				break;

			case 5:
			    /* Asks user to input 2 team abbreviations (see Documentation for list of
                correct abbreviations).  Then calls the compareTeams public functions
                with the 2 user inputs.*/
				cout << "Enter Team 1 Abbreviation:" << endl;
				getline(cin,in_string1);
				cout << "Enter Team 2 Abbreviation:" << endl;
				getline(cin,in_string2);
				FFData->compareTeams(in_string1, in_string2);
				break;

			case 6:
			    /* Asks user to input 2 indexes between 1 and 200.  Then calls the
                entrySelect public function using the user inputs.*/
				cout << "Range of Indices (1-200)" << endl;
				cout << "Enter starting index:" << endl;
				cin >> index1;
				cout << "Enter ending index:" << endl;
				cin >> index2;
				FFData->entrySelect(index1, index2);
				break;

            case 7:
                // Calls the destructor public function to clear out the database.
                FFData->~Database();
                cout << "Database cleared." << endl;
                break;

			case 8:
			    // Quit option was selected and while loop is exited.
				quit = true;
				cout << "Goodbye!" << endl;
				break;
		}
	}
}
