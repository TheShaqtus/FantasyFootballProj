#ifndef FOOTBALL_H
#define FOOTBALL_H


struct player{
	int games;
	std::string name;
	std::string team;
	std::string position;
	int points;
	float avgPoints;
	player* prev;
	player* next;

	player(){};

	player(std::string in_name, std::string in_team, int in_games, std::string in_position, int in_points){
		name = in_name;
		team = in_team;
		games = in_games;
		position = in_position;
		points = in_points;
		avgPoints = points/games;
		next = NULL;
		prev = NULL;
	}
};

class Database
{

	public:
		Database();
		~Database();
		void buildDatabase(char * fileName);
		void printDatabase();
		void comparePlayers(std::string, std::string);
		void bubbleSort();
		void mergeSort();
		void insertionSort();
		void compareTeams(std::string, std::string);
		void entrySelect(int, int);
	protected:
	private:
		player* root;
		int entryCount;

};





#endif
