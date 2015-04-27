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
	 //if(fileName.is_open){
	 ifstream myFile(fileName);
        string line;
        entryCount=0;
        player* temp = root;

        while(getline(myFile, line)){
            int indexOfSpace=line.find(",");
            //int length=line.length();
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
            if(entryCount == 0){
                root->name = name;
                root->team = team;
                root->games= games;
                root->points= playerpoints;
                root->position= position;
                root->avgPoints= (playerpoints/(double)games);
            }
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
            entryCount++;
        }
	//}
    cout << "Database built." << endl;



}

void Database::printDatabase(){
    player* curr = root;
    cout << "Name   Team   Position   Games Played   Points   Points/Game" << endl;
    while(curr != NULL){
        cout << curr->name << "  " << curr->team << "  " << curr->position << "  " << curr->games << "  " << curr->points << "  " << fixed << setprecision(2) << curr->avgPoints  << endl;
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

    mergeRun(input1, input2, root);
    cout << "Sort complete." << endl;

}

void Database::insertionSort(){
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
    root = insertionRun(root, input1, input2);
    cout << "Sort complete." << endl;
}

void Database::entrySelect(int index1, int index2){
    player* head = root;
    player* tail = NULL;
    player* curr;
    int numEntries = index2-index1+1;
    int pointSum = 0;
    int gameSum = 0;
    double avgPoints = 0.0;
    for(int i = 1; i < index1; i++){
        head = head->next;
    }
    tail = head->next;
    for(int j = 0; j < index2-index1; j++){
        tail = tail->next;
    }
    curr = head;
    while(curr->name.compare(tail->name) != 0){
        cout << curr->name << "  " << curr->team << "  " << curr->position << "  " << curr->games << "  " << curr->points << "  " << fixed << setprecision(2) << curr->avgPoints  << endl;
        pointSum = pointSum + curr->points;
        gameSum = gameSum +curr->games;
        curr = curr->next;

    }
    avgPoints = pointSum / (double)gameSum;
    cout << "Average Points: " << fixed << setprecision(2) << pointSum/(double)numEntries << endl;
    cout << "Average Games Played: " << fixed << setprecision(2) << gameSum / (double)numEntries << endl;
    cout << "Average Points Per Game: " << fixed << setprecision(2) << avgPoints << endl;

}

player* mergeRun(int input1, int input2, player* head){
    if(head == NULL || head->next == NULL){
        return head;
    }
    player* middle = listSplit(head);
    player* secondHalf = middle->next;
    middle->next = NULL;
    return Merge(mergeRun(input1, input2, head), mergeRun(input1, input2, secondHalf), input1, input2);

}

player* listSplit(player* head){

    if(head == NULL){
        return head;
    }
    player* slow = head;
    player* fast = head;
    while(fast->next != NULL && fast->next->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

player* Merge(player* x, player* y, int input1, int input2){

    player* temp = new player;
    player* curr = temp;
    while(x != NULL && y != NULL){
        if(x->name.compare(y->name) < 0){
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
}

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
