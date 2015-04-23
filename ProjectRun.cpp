#include <iostream>
#include "Football.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <stdlib.h> //allows atoi
#include <vector>

using namespace std;

int main(int argc, char*argv[]){
	
	int input;
	int sort;
	int index1, index2;
	string in_string1;
	string in_string2;
	char* fileName = argv[1];
	Database* FFData = new Database();
	bool quit = false;
	
	while(quit != true){
		
		cout << "====MENU====" << endl;
		cout << "1. Build Database" << endl;
		cout << "2. Print Database" << endl;
		cout << "3. Sort Database" << endl;
		cout << "4. Compare Players" << endl;
		cout << "5. Compare Teams" << endl;
		cout << "6. Select Database Entries" << endl;
		cout << "7. Quit" << endl;
		
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');
		
		switch(input){
			
			case 1:
				FFData->buildDatabase(fileName);
				break;
				
			case 2:
				FFData->printDatabase();
				break;
			
			case 3:
				cout << "==Choose Sort Method==" << endl;
				cout << "1. Bubble Sort" << endl;
				cout << "2. Insertion Sort" << endl;
				cout << "3. Merge Sort" << endl;
				cin >> sort;
				if(sort == 1){
					FFData->bubbleSort();
					break;
				}else if(sort == 2){
					FFData->insertionSort();
					break;
				}else if(sort == 3){
					FFData->mergeSort();
					break;
				}else{
					cout << "Not a valid choice." << endl;
				}
				
			case 4:
				cout << "Enter Player 1 Name:" << endl;
				getline(cin,in_string1);
				cout << "Enter Player 2 Name:" << endl;
				getline(cin,in_string2);
				FFData->comparePlayers(in_string1, in_string2);
				break;
				
			case 5:
				cout << "Enter Team 1 Abbreviation:" << endl;
				getline(cin,in_string1);
				cout << "Enter Team 2 Abbreviation:" << endl;
				getline(cin,in_string2);
				FFData->compareTeams(in_string1, in_string2);
				break;
				
			case 6:
				cout << "Range of Indices (1-200)" << endl;
				cout << "Enter starting index:" << endl;
				cin >> index1;
				cout << "Enter ending index:" << endl;
				cin >> index2;
				FFData->entrySelect(index1, index2);
				break;
			
			case 7:
				quit = true;
				break;
		}
	}
}
				
