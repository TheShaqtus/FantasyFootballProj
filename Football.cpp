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
    player* curr = root;
    cout << "Name   Team   Position   Games Played   Points   Points/Game" << endl;
    while(curr != NULL){
        cout << curr->name << "  " << curr->team << "  " << curr->position << "  " << curr->games << "  " << curr->points << "  " << curr->avgPoints << endl;
        curr = curr->next;
    }
}

void Database::comparePlayers(string name1, string name2){
    player* curr = root;
    int count = 2;
    player* player1;
    player* player2;
    int gamesDel = 0;
    int pointsDel = 0;
    float avgPointsDel = 0;

    while(curr != NULL){
        if(curr->name.compare(name1) == 0){

            count--;
            player1 = curr;
        }else if(curr->name.compare(name2) == 0){

            count--;
            player2 = curr;
        }
        if(count == 0){
            break;
        }
        curr = curr->next;
    }
    if(count != 0){
        cout << "Player(s) not found." << endl;
        return;
    }
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
