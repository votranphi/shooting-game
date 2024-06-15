#pragma once
#include "Formation.h"
#include <string>
#include <time.h>
#include <map>
#include <vector>

#define DELAY_TIME_OF_YOUR_ATTACK 3000 // delay time in milisecond
#define DELAY_TIME_OF_ENEMY_ATTACK 3000 // delay time in milisecond

#define MAX_SOLDIERS_IN_EACH_FLANK 60 // maximum: 60
#define MAX_SOLDIERS_IN_FRONT 240 // maximum: 240
#define MAX_SOLDIERS_IN_LONGRANGE 96 // maximum: 96

class Game
{
	Formation enemy;
	Formation myTeam;
	map<string, int> stringToInt;
	vector<string> intToString;

public:
	Game();

	int random(const int&, const int&);
	string formatInt(const int&);
	string getSoldierType(Line*, const int&);

	void randomEnemy(); // This method generates randomly enemy's Formation
	void randomMyTeam(); // This method generates randomly myTeam's Formation
	void inputMyTeam(); // This method generates myTeam's Formation following user's requirements
	void output(); // Execute this method will output enemy's Formation and myTeam's Formation

	bool isEnemyLose(); // or isEnemyFormationEmpty
	bool isMyTeamLose(); // or isMyTeamFormationEmpty

	void enemyAttack(); // or enemyAutoAttack
	void myTeamAutoAttack();
	void myTeamAttack(const string&, string&);
};