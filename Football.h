#ifndef FOOTBALL_H
#define FOOTBALL_H

struct node{
	int games;
	std::string name;
	std::string team;
	std::string position;
	int points;
	float avgPoints;
	node* prev;
	node* next;
	
	node(){};
	
	node(std::string in_name, std::string in_team, int in_games, std::string in_position, int in_points){
		name = in_name;
		team = in_team;
		games = in_games;
		position = in_position;
		points = in_points;
		avgPoints = points/games;
		next = NULL;
		prev = NULL;
};

class StatTree{
	
	public:
		StatTree();
		~StatTree();
		void addPlayer(std::string, std::string, int, std::string, int);
		void printTree();
		void printByPosition(std::string);
		void comparePlayers(std::string, std::string);
		


#endif
