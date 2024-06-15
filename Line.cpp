#include "Line.h"

Line::Line() : capacity(0), slot(0)
{

}

Line::Line(const int& capacity, const int& slot) : capacity(capacity), slot(slot), all(vector<vector<Army*>> (slot, vector<Army*> (capacity / slot, nullptr)))
{

}

int Line::armyCounting()
{
	int count = 0;
	for (int i = 0; i < slot; i++)
	{
		for (int j = 0; j < capacity / slot; j++)
		{
			if (all[i][j] != nullptr)
			{
				count++;
			}
		}
	}

	return count;
}

int Line::armyCounting(const int& slotIdx)
{
	int count = 0;

	for (int i = 0; i < capacity / slot; i++)
	{
		if (all[slotIdx][i] != nullptr)
		{
			count++;
		}
	}

	return count;
}

void Line::beAttacked(Line* attacker)
{
	int totalDamageTaken = 0;
	for (int i = 0; i < attacker->slot; i++)
	{
		for (int j = 0; j < attacker->capacity / attacker->slot; j++)
		{
			if (attacker->all[i][j] != nullptr)
			{
				totalDamageTaken += attacker->all[i][j]->getDamage();
			}
		}
	}


	for (int i = 0; i < slot; i++)
	{
		bool isBreakThisLoop = false;

		for (int j = 0; j < capacity / slot; j++)
		{
			if (totalDamageTaken != 0)
			{
				if (all[i][j] != nullptr)
				{
					all[i][j]->beAttacked(totalDamageTaken);
					if (all[i][j]->getBlood() == 0)
					{
						// delete all[i][j];
						all[i][j] = nullptr;
					}
				}
			}
			else
			{
				isBreakThisLoop = true;
				break;
			}
		}

		if (isBreakThisLoop)
		{
			break;
		}
	}
}

bool Line::isEmpty()
{
	for (int i = 0; i < slot; i++)
	{
		for (int j = 0; j < capacity / slot; j++)
		{
			if (all[i][j] != nullptr)
			{
				return false;
			}
		}
	}

	return true;
}

Line::~Line()
{
	//for (int i = 0; i < slot; i++)
	//{
	//	for (int j = 0; j < capacity / slot; j++)
	//	{
	//		delete all[i][j];
	//	}
	//}
}
