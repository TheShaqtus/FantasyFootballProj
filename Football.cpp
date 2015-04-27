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
	 if(fileName.is_open){
        string line;
        entryCount=0;
        player* temp = root;

        while(getline(fileName, line)){
            int indexOfSpace=line.find(",");
            int length=line.length();
            string name= line.substr(0, indexOfSpace);
            string secondline= line.substr(indexOfSpace+1);
            int indexOfSpace2=secondline.find(",");
            string team= secondline.substr(0, indexOfSpace2);
            string thirdline = secondline.substr(indexOfSpace2+1);
            int indexOfSpace3 = thirdline.find(",");
            string number= thirdline.substr(0, indexOfSpace3);
            int games= atoi(number);
            string fourthline= thirdline.substr(indexOfSpace3+1);
            int indexOfSpace4= fourthline.find(",");
            string position=fourthline.substr(0, indexOfSpace4);
            string points=fourthline.substr(indexOfSpace4+1);
            int playerpoints= atoi(points);
            if(entryCount == 0){
                root->name = name;
                root->team = team;
                root->games= games;
                root->points= playerpoints;
                root->position= position;
                root->avgPoints= (playerpoints/games);
            }
            else{
                player* n = new player;
                n->name = name;
                n->team = team;
                n->games= games;
                n->points= playerpoints;
                n->position= position;
                n->avgPoints= (playerpoints/games);
                temp->next = n;
            }
            entryCount++;
            temp = temp->next;
        }
	}
    cout << "Database built." << endl;



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
    int input1;
    int input2;
    player* curr = NULL;
    player* trail = NULL;
    player* temp = NULL;
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

    switch(input1){

        case 1:
            if(input2 == 1){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        if(curr->name.compare(curr->next->name) > 0){
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
            }else if(input2 == 2){
                for(int i = 0; i < entryCount; i++){
                    curr = trail = root;
                    while(curr->next != NULL){
                        if(curr->name.compare(curr->next->name) < 0){
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

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;



    }
    cout << "Sort complete." << endl;
}

void Database::mergeSort(){

}

void Database::insertionSort(){
}

void Database::entrySelect(int index1, int index2){
}
