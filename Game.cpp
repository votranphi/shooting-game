#include "Game.h"
#include "Powder.h"
#include "Hop.h"
#include "Sword.h"
#include "Spear.h"
#include <iostream>
#include <windows.h>
using namespace std;

Game::Game()
{
	stringToInt["LeftFlank"] = 0;
	stringToInt["RightFlank"] = 1;
	stringToInt["Front"] = 2;
	stringToInt["LongRange"] = 3;

	intToString = vector<string>(4);
	intToString[0] = "LeftFlank";
	intToString[1] = "RightFlank";
	intToString[2] = "Front";
	intToString[3] = "LongRange";
}

int Game::random(const int& min, const int& max)
{
	return min + rand() % (max - min + 1);
}

string Game::formatInt(const int& number)
{
	if (number / 10 == 0)
	{
		return '0' + to_string(number);
	}
	else
	{
		return to_string(number);
	}
}

string Game::getSoldierType(Line* line, const int& slotIdx)
{
	int i = 0;
	while (i < line->capacity / line->slot && line->all[slotIdx][i] == nullptr)
	{
		i++;
	}

	if (i == line->capacity / line->slot)
	{
		return "So";
	}

	if (line->all[slotIdx][i] != nullptr)
	{
		ArmyType type = line->all[slotIdx][i]->getType();
		switch (type)
		{
		case powder:
			return "Po";
		case hop:
			return "Ho";
		case sword:
			return "Sw";
		case spear:
			return "Sp";
		}
	}
	else
	{
		return "So";
	}
}

void Game::randomEnemy()
{
	vector<Army*> randomGroup (MAX_SOLDIERS_IN_EACH_FLANK, nullptr);
	for (int i = 0; i < MAX_SOLDIERS_IN_EACH_FLANK; i++) // 2 Flanks
	{
		int randInt = random(0, 1);
		if (randInt == 0)
		{
			randomGroup[i] = new Sword;
		}
		else
		{
			randomGroup[i] = new Spear;
		}
	}
	enemy.line[0]->arrange(randomGroup);
	enemy.line[1]->arrange(randomGroup);
	enemy.line[0]->virtualArmor(VIRTUAL_ARMOR_OF_SOLDIERS_IN_TWO_FLANKS);
	enemy.line[1]->virtualArmor(VIRTUAL_ARMOR_OF_SOLDIERS_IN_TWO_FLANKS);

	randomGroup = vector<Army*>(MAX_SOLDIERS_IN_FRONT, nullptr);
	for (int i = 0; i < MAX_SOLDIERS_IN_FRONT; i++) // Front
	{
		int randInt = random(0, 2);
		if (randInt == 0)
		{
			randomGroup[i] = new Hop;
		}
		else if (randInt == 1)
		{
			randomGroup[i] = new Sword;
		}
		else
		{
			randomGroup[i] = new Spear;
		}
	}
	enemy.line[2]->arrange(randomGroup);

	randomGroup = vector<Army*>(MAX_SOLDIERS_IN_LONGRANGE, nullptr);
	for (int i = 0; i < MAX_SOLDIERS_IN_LONGRANGE; i++) // LongRange
	{
		randomGroup[i] = new Powder;
	}
	enemy.line[3]->arrange(randomGroup);
}

void Game::randomMyTeam()
{
	vector<Army*> randomGroup(MAX_SOLDIERS_IN_EACH_FLANK, nullptr);
	for (int i = 0; i < MAX_SOLDIERS_IN_EACH_FLANK; i++) // 2 Flanks
	{
		int randInt = random(0, 1);
		if (randInt == 0)
		{
			randomGroup[i] = new Sword;
		}
		else
		{
			randomGroup[i] = new Spear;
		}
	}
	myTeam.line[0]->arrange(randomGroup);
	myTeam.line[1]->arrange(randomGroup);
	myTeam.line[0]->virtualArmor(VIRTUAL_ARMOR_OF_SOLDIERS_IN_TWO_FLANKS);
	myTeam.line[1]->virtualArmor(VIRTUAL_ARMOR_OF_SOLDIERS_IN_TWO_FLANKS);

	randomGroup = vector<Army*>(MAX_SOLDIERS_IN_FRONT, nullptr);
	for (int i = 0; i < MAX_SOLDIERS_IN_FRONT; i++) // Front
	{
		int randInt = random(0, 2);
		if (randInt == 0)
		{
			randomGroup[i] = new Hop;
		}
		else if (randInt == 1)
		{
			randomGroup[i] = new Sword;
		}
		else
		{
			randomGroup[i] = new Spear;
		}
	}
	myTeam.line[2]->arrange(randomGroup);

	randomGroup = vector<Army*>(MAX_SOLDIERS_IN_LONGRANGE, nullptr);
	for (int i = 0; i < MAX_SOLDIERS_IN_LONGRANGE; i++) // LongRange
	{
		randomGroup[i] = new Powder;
	}
	myTeam.line[3]->arrange(randomGroup);
}

void Game::inputMyTeam()
{
	int numberOfPowder;
	int numberOfHop;
	int numberOfSword;
	int numberOfSpear;

	cout << "\033[31m" << "INITIALIZE YOUR TEAM" << "\033[0m" << '\n';
	cout << "Please enter 2 integers indicate number of Sword and Spear soldiers IN TWO FLANK LINES respectively (0 < total soldier <= " << MAX_SOLDIERS_IN_EACH_FLANK << "): ";
	cin >> numberOfSword >> numberOfSpear;
	int totalSoldier = numberOfSword + numberOfSpear;
	vector<Army*> group(totalSoldier, nullptr);
	for (int i = 0; i < totalSoldier; i++) // 2 Flanks
	{
		if (i < numberOfSword)
		{
			group[i] = new Sword;
		}
		else
		{
			group[i] = new Spear;
		}
	}
	myTeam.line[0]->arrange(group);
	myTeam.line[1]->arrange(group);
	myTeam.line[0]->virtualArmor(VIRTUAL_ARMOR_OF_SOLDIERS_IN_TWO_FLANKS);
	myTeam.line[1]->virtualArmor(VIRTUAL_ARMOR_OF_SOLDIERS_IN_TWO_FLANKS);

	cout << "Please enter 3 integers indicate number of Hop, Sword and Spear soldiers IN THE FRONT LINE respectively (0 < total soldier <= " << MAX_SOLDIERS_IN_FRONT << "): ";
	cin >> numberOfHop >> numberOfSword >> numberOfSpear;
	totalSoldier = numberOfHop + numberOfSword + numberOfSpear;
	group = vector<Army*>(totalSoldier, nullptr);
	for (int i = 0; i < totalSoldier; i++) // Front
	{
		if (i < numberOfHop)
		{
			group[i] = new Hop;
		}
		else if (i >= numberOfHop && i < numberOfHop + numberOfSword)
		{
			group[i] = new Sword;
		}
		else
		{
			group[i] = new Spear;
		}
	}
	myTeam.line[2]->arrange(group);

	cout << "Please enter 1 integer indicates number of Powder soldiers IN THE LONGRANGE LINES (0 < total soldier <= " << MAX_SOLDIERS_IN_LONGRANGE << "): ";
	cin >> numberOfPowder;
	group = vector<Army*>(numberOfPowder, nullptr);
	for (int i = 0; i < numberOfPowder; i++) // LongRange
	{
		group[i] = new Powder;
	}
	myTeam.line[3]->arrange(group);
}

void Game::output()
{
	cout << "\033[33m" << string(46, '-') << "ENEMY'S TEAM AND YOUR TEAM RIGHT NOW" << string(47, '-') << "\033[0m" << string(10, ' ') << "\033[36m" << "ABBREVIATION" << "\033[0m" << '\n';
	for (int i = 1; i <= 19; i++)
	{
		if (i == 1) {
			cout << string(32, ' ') << string(65, '-') << string(32 + 10, ' ') << "\033[36m" << "Po: Powder" << "\033[0m";
		}
		else if (i == 2) { // enemy's LongRange
			cout << string(32, ' ');
			int slotIdx = 0;
			int typeIdx = 0;
			for (int j = 33; j <= 97; j++) {
				if (j % 8 == 1)
					cout << '|';
				if (j % 8 == 2 || j % 8 == 5 || j % 8 == 0)
					cout << ' ';
				if (j % 8 == 3) {
					cout << formatInt(enemy.line[3]->armyCounting(slotIdx));
					slotIdx++;
					j++;
				}
				if (j % 8 == 6)
				{
					cout << getSoldierType(enemy.line[3], typeIdx);
					typeIdx++;
					j++;
				}
			}
			cout << string(32 + 10, ' ') << "\033[36m" << "Ho: Hop" << "\033[0m";
		}
		else if (i == 3) {
			cout << string(32, ' ') << string(65, '-') << string(32 + 10, ' ') << "\033[36m" << "Sw: Sword" << "\033[0m";
		}
		else if (i == 4) {
			cout << string(56, ' ') << "\033[31m" << "Enemy's LongRange" << "\033[0m" << string(56 + 10, ' ') << "\033[36m" << "Sp: Spear" << "\033[0m";
		}
		else if (i == 5) {
			cout << string(25, '-') << string(7, ' ') << string(65, '-') << string(7, ' ') << string(25, '-') << string(10, ' ') << "\033[36m" << "So: Sodier" << "\033[0m";
		}
		else if (i == 6) { // enemy's right Flank, Front, left Flank
			int slotIdx = 0;
			int typeIdx = 0;
			for (int j = 1; j <= 25; j++) // right Flank
			{
				if (j % 8 == 1)
					cout << '|';
				if (j % 8 == 2 || j % 8 == 5 || j % 8 == 0)
					cout << ' ';
				if (j % 8 == 3) {
					cout << formatInt(enemy.line[1]->armyCounting(slotIdx));
					slotIdx++;
					j++;
				}
				if (j % 8 == 6)
				{
					cout << getSoldierType(enemy.line[1], typeIdx);
					typeIdx++;
					j++;
				}
			}
			cout << string(7, ' ');
			slotIdx = 0;
			typeIdx = 0;
			for (int j = 33; j <= 97; j++) // Front
			{
				if (j % 8 == 1)
					cout << '|';
				if (j % 8 == 2 || j % 8 == 5 || j % 8 == 0)
					cout << ' ';
				if (j % 8 == 3) {
					cout << formatInt(enemy.line[2]->armyCounting(slotIdx));
					slotIdx++;
					j++;
				}
				if (j % 8 == 6)
				{
					cout << getSoldierType(enemy.line[2], typeIdx);
					typeIdx++;
					j++;
				}
			}
			cout << string(7, ' ');
			slotIdx = 0;
			typeIdx = 0;
			for (int j = 105; j <= 129; j++) // left Flank
			{
				if (j % 8 == 1)
					cout << '|';
				if (j % 8 == 2 || j % 8 == 5 || j % 8 == 0)
					cout << ' ';
				if (j % 8 == 3) {
					cout << formatInt(enemy.line[0]->armyCounting(slotIdx));
					slotIdx++;
					j++;
				}
				if (j % 8 == 6)
				{
					cout << getSoldierType(enemy.line[0], typeIdx);
					typeIdx++;
					j++;
				}
			}
		}
		else if (i == 7) {
			cout << string(25, '-') << string(7, ' ') << string(65, '-') << string(7, ' ') << string(25, '-');
		}
		else if (i == 8) {
			cout << string(3, ' ') << "\033[31m" << "Enemy's RightFlank" << "\033[0m" << string(4 + 7 + 26, ' ') << "\033[31m" << "Enemy's Front" << "\033[0m" << string(27 + 7 + 4, ' ') << "\033[31m" << "Enemy's LeftFlank" << "\033[0m";
		}
		else if (i == 12) {
			cout << string(5, ' ') << "\033[32m" << "Your LeftFlank" << "\033[0m" << string(6 + 7 + 27, ' ') << "\033[32m" << "Your Front" << "\033[0m" << string(28 + 7 + 5, ' ') << "\033[32m" << "Your RightFlank" << "\033[0m";
		}
		else if (i == 13) {
			cout << string(25, '-') << string(7, ' ') << string(65, '-') << string(7, ' ') << string(25, '-');
		}
		else if (i == 14) { // myTeam's left Flank, Front, right Flank
			int slotIdx = 0;
			int typeIdx = 0;
			for (int j = 1; j <= 25; j++) // left Flank
			{
				if (j % 8 == 1)
					cout << '|';
				if (j % 8 == 2 || j % 8 == 5 || j % 8 == 0)
					cout << ' ';
				if (j % 8 == 3) {
					cout << formatInt(myTeam.line[0]->armyCounting(slotIdx));
					slotIdx++;
					j++;
				}
				if (j % 8 == 6)
				{
					cout << getSoldierType(myTeam.line[0], typeIdx);
					typeIdx++;
					j++;
				}
			}
			cout << string(7, ' ');
			slotIdx = 0;
			typeIdx = 0;
			for (int j = 33; j <= 97; j++) // Front
			{
				if (j % 8 == 1)
					cout << '|';
				if (j % 8 == 2 || j % 8 == 5 || j % 8 == 0)
					cout << ' ';
				if (j % 8 == 3) {
					cout << formatInt(myTeam.line[2]->armyCounting(slotIdx));
					slotIdx++;
					j++;
				}
				if (j % 8 == 6)
				{
					cout << getSoldierType(myTeam.line[2], typeIdx);
					typeIdx++;
					j++;
				}
			}
			cout << string(7, ' ');
			slotIdx = 0;
			typeIdx = 0;
			for (int j = 105; j <= 129; j++) // right Flank
			{
				if (j % 8 == 1)
					cout << '|';
				if (j % 8 == 2 || j % 8 == 5 || j % 8 == 0)
					cout << ' ';
				if (j % 8 == 3) {
					cout << formatInt(myTeam.line[1]->armyCounting(slotIdx));
					slotIdx++;
					j++;
				}
				if (j % 8 == 6)
				{
					cout << getSoldierType(myTeam.line[1], typeIdx);
					typeIdx++;
					j++;
				}
			}
		}
		else if (i == 15) {
			cout << string(25, '-') << string(7, ' ') << string(65, '-') << string(7, ' ') << string(25, '-');
		}
		else if (i == 16) {
			cout << string(57, ' ') << "\033[32m" << "Your LongRange" << "\033[0m" << string(58, ' ');
		}
		else if (i == 17) {
			cout << string(32, ' ') << string(65, '-') << string(32, ' ');
		}
		else if (i == 18) { // myTeam's LongRange
			cout << string(32, ' ');
			int slotIdx = 0;
			int typeIdx = 0;
			for (int j = 33; j <= 97; j++) {
				if (j % 8 == 1)
					cout << '|';
				if (j % 8 == 2 || j % 8 == 5 || j % 8 == 0)
					cout << ' ';
				if (j % 8 == 3) {
					cout << formatInt(myTeam.line[3]->armyCounting(slotIdx));
					slotIdx++;
					j++;
				}
				if (j % 8 == 6)
				{
					cout << getSoldierType(myTeam.line[3], typeIdx);
					typeIdx++;
					j++;
				}
			}
			cout << string(32, ' ');
		}
		else if (i == 19) {
			cout << string(32, ' ') << string(65, '-') << string(32, ' ');
		}
		cout << '\n';
	}
	cout << "\033[33m" << string(129, '-') << "\033[0m" << '\n';
}

bool Game::isEnemyLose()
{
	bool isLose = true;
	for (int i = 0; i < 4; i++)
	{
		isLose = isLose && enemy.line[i]->isEmpty();
	}

	return isLose;
}

bool Game::isMyTeamLose()
{
	bool isLose = true;
	for (int i = 0; i < 4; i++)
	{
		isLose = isLose && myTeam.line[i]->isEmpty();
	}

	return isLose;
}

void Game::enemyAttack()
{
	int attacker;
	int beAttacked;
	do // Loop until enemy's selected line isn't empty
	{
		attacker = random(0, 3);
	} while (enemy.line[attacker]->isEmpty());

	if (myTeam.line[2]->isEmpty()) // If myTeam's Front line is empty
	{
		do // Loop until myTeam's selected line isn't empty with no exception
		{
			beAttacked = random(0, 3);
		} while (myTeam.line[beAttacked]->isEmpty());
	}
	else // If myTeam's Front line isn't empty
	{
		do // Loop until myTeam's selected line isn't empty except myTeam's LongRange line
		{
			beAttacked = random(0, 2);
		} while (myTeam.line[beAttacked]->isEmpty());
	}

	myTeam.line[beAttacked]->beAttacked(enemy.line[attacker]);

	cout << "\033[1m" << "\033[31m" << "Enemy is attacking your " << intToString[beAttacked] << " using their " << intToString[attacker] << "\033[0m" << "\033[0m";
	for (int i = 0; i < 6; i++)
	{
		Sleep(DELAY_TIME_OF_ENEMY_ATTACK / 6);
		cout << "\033[1m" << "\033[31m" << '.' << "\033[0m" << "\033[0m";
	}
	cout << '\n';
}

void Game::myTeamAutoAttack()
{
	int attacker;
	int beAttacked;
	do // Loop until myTeam's selected line isn't empty
	{
		attacker = random(0, 3);
	} while (myTeam.line[attacker]->isEmpty());

	if (enemy.line[2]->isEmpty()) // If enemy's Front line is empty
	{
		do // Loop until enemy's selected line isn't empty with no exception
		{
			beAttacked = random(0, 3);
		} while (enemy.line[beAttacked]->isEmpty());
	}
	else // If enemy's Front line isn't empty
	{
		do // Loop until enemy's selected line isn't empty except enemy's LongRange line
		{
			beAttacked = random(0, 2);
		} while (enemy.line[beAttacked]->isEmpty());
	}

	enemy.line[beAttacked]->beAttacked(myTeam.line[attacker]);

	cout << "\033[1m" << "\033[32m" << "You're attacking enemy's " << intToString[beAttacked] << " using your " << intToString[attacker] << "\033[0m" << "\033[0m";
	for (int i = 0; i < 6; i++)
	{
		Sleep(DELAY_TIME_OF_YOUR_ATTACK / 6);
		cout << "\033[1m" << "\033[32m" << '.' << "\033[0m" << "\033[0m";
	}
	cout << '\n';
}

void Game::myTeamAttack(const string& attacker, string& beAttacked)
{
	while (beAttacked == "LongRange" && !enemy.line[2]->isEmpty()) // Loop while enemy's attacked line is LongRange and enemy's Front line isn't empty
	{
		cout << "You " << "\033[31m" << "CANNOT" << "\033[0m" << " use your " << attacker << " to attack enemy's LongRange! Please select enemy's line again: ";
		cin >> beAttacked;
	}

	enemy.line[stringToInt[beAttacked]]->beAttacked(myTeam.line[stringToInt[attacker]]);

	cout << "\033[1m" << "\033[32m" << "You're attacking enemy's " << beAttacked << " using your " << attacker << "\033[0m" << "\033[0m";
	for (int i = 0; i < 6; i++)
	{
		Sleep(DELAY_TIME_OF_YOUR_ATTACK / 6);
		cout << "\033[1m" << "\033[32m" << '.' << "\033[0m" << "\033[0m";
	}
	cout << '\n';
}
