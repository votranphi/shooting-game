#include "Army.h"
#include "Powder.h"
#include "Hop.h"
#include "Sword.h"
#include "Spear.h"
#include "Line.h"
#include "Flank.h"
#include "Front.h"
#include "LongRange.h"
#include "Formation.h"
#include "Game.h"
#include <iostream>
#include <map>
using namespace std;

int main()
{
	srand(time(nullptr));

	Game hihi;

	hihi.randomEnemy(); // Random enemy's team
	string selection;
	cout << "Do you want your team to be generated randomly? (Yes/No): ";
	cin >> selection;
	while (selection != "Yes" && selection != "No")
	{
		cout << "Please enter \"Yes\" or \"No\": ";
		cin >> selection;
	}
	if (selection == "Yes") // Randomly generate myTeam
	{
		hihi.randomMyTeam();
	}
	else if (selection == "No") // Generate myTeam base on user's input
	{
		hihi.inputMyTeam();
	}

	system("cls");
	hihi.output();

	string attacker;
	string beAttacked;
	cout << "Do you want your team to attack enemy automatically? (Yes/No): ";
	cin >> selection;
	while (selection != "Yes" && selection != "No")
	{
		cout << "Please enter \"Yes\" or \"No\": ";
		cin >> selection;
	}
	system("cls");
	hihi.output();
	int round = 1;
	if (selection == "Yes") // myTeam automatically attacks enemy
	{
		while (!hihi.isEnemyLose() && !hihi.isMyTeamLose())
		{
			cout << string(60, ' ') << "\033[35m" << "ROUND " << hihi.formatInt(round) << "\033[0m" << string(61, ' ') << '\n';

			hihi.myTeamAutoAttack();
			// If enemy's Formation is empty after getting attacked by user, we won't run the command at line 71 (BUG FIXED)
			if (hihi.isEnemyLose())
			{
				system("cls");
				hihi.output();
				break;
			}

			system("cls");
			hihi.output();
			cout << string(60, ' ') << "\033[35m" << "ROUND " << hihi.formatInt(round) << "\033[0m" << string(61, ' ') << '\n';

			hihi.enemyAttack();
			system("cls");
			hihi.output();

			round++;
		}
	}
	else if (selection == "No") // myTeam attacks enemy base on the user's input
	{
		while (!hihi.isEnemyLose() && !hihi.isMyTeamLose())
		{
			cout << string(60, ' ') << "\033[35m" << "ROUND " << hihi.formatInt(round) << "\033[0m" << string(61, ' ') << '\n';

			cout << "Select enemy's line which you want to attack it (LeftFlank, RightFlank, Front or LongRange): ";
			cin >> beAttacked;
			cout << "Select your line which you want it to attack enemy's line (LeftFlank, RightFlank, Front or LongRange): ";
			cin >> attacker;

			hihi.myTeamAttack(attacker, beAttacked);
			// If enemy's Formation is empty after getting attacked by user, we won't run the command at line 97 (BUG FIXED)
			if (hihi.isEnemyLose())
			{
				system("cls");
				hihi.output();
				break;
			}

			system("cls");
			hihi.output();
			cout << string(60, ' ') << "\033[35m" << "ROUND " << hihi.formatInt(round) << "\033[0m" << string(61, ' ') << '\n';

			hihi.enemyAttack();
			system("cls");
			hihi.output();

			round++;
		}
	}

	if (hihi.isEnemyLose()) // Print the result
	{
		cout << string(52, ' ') << "\033[1m" << "\033[31m" << "CONGRATULATIONS! YOU WIN!" << "\033[0m" << "\033[0m" << string(52, ' ');
	}
	else if (hihi.isMyTeamLose())
	{
		cout << string(54, ' ') << "\033[1m" << "\033[31m" << "UNLUCKILY! YOU LOSE!" << "\033[0m" << "\033[0m" << string(55, ' ');
	}

	cout << '\n';
	system("pause");

	return 0;
};