#include <iostream>
#include "Football.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <stdlib.h> //allows atoi
#include <vector>

using namespace std;

Database::Database()
{
	player* temp = new player("", "", 1, "", 0);
	root = temp;
	temp->prev = NULL;
	temp->next = NULL;
}

Database::~Database()
{
	player* curr = root;
	player* del;
	while(curr!=NULL){
		del = curr;
		curr = curr->next;
		delete del;
	}
}

void Database::buildDatabase(char* fileName){
	
	
}

void Database::printDatabase(){
}

void Database::comparePlayers(string name1, string name2){
}

void Database::compareTeams(string name1, string name2){
}

void Database::bubbleSort(){
}

void Database::mergeSort(){
}

void Database::insertionSort(){
}

void Database::entrySelect(int index1, int index2){
}
