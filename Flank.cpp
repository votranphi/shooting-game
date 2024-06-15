#include "Flank.h"
#include <stack>

Flank::Flank(const bool& isLeft) : isLeft(isLeft), Line(CAPACITY_OF_FLANK, SLOT_OF_FLANK)
{
	
}

void Flank::arrange(vector<Army*>& group)
{
	// Store all the soldiers in the group to a stack in order: Spear first, then Sword
	stack<Army*> groupStack;
	for (int i = 0; i < group.size(); i++)
	{
		if (group[i]->getType() == spear)
		{
			groupStack.push(group[i]);
		}
	}
	for (int i = 0; i < group.size(); i++)
	{
		if (group[i]->getType() == sword)
		{
			groupStack.push(group[i]);
		}
	}

	// Arrange the soldiers in the stack to the Flank line
	for (int i = 0; i < slot; i++)
	{
		bool isSwordInSlot = false;
		int j;
		for (j = 0; j < capacity / slot && all[i][j] != nullptr; j++)
		{
			if (all[i][j]->getType() == sword)
			{
				isSwordInSlot = true;
			}
		}

		if (j < capacity / slot)
		{
			if (isSwordInSlot)
			{
				while (j < capacity / slot && !groupStack.empty() && groupStack.top()->getType() == sword)
				{
					all[i][j++] = groupStack.top();
					groupStack.pop();
				}
			}
			else
			{
				if (j == 0)
				{
					ArmyType firstTypeInStack = groupStack.top()->getType();
					while (j < capacity / slot && !groupStack.empty() && groupStack.top()->getType() == firstTypeInStack)
					{
						all[i][j++] = groupStack.top();
						groupStack.pop();
					}
				}
				else
				{
					while (j < capacity / slot && !groupStack.empty() && groupStack.top()->getType() == spear)
					{
						all[i][j++] = groupStack.top();
						groupStack.pop();
					}
				}
			}
		}

		if (groupStack.empty())
		{
			break;
		}
	}
}

void Flank::virtualArmor(const int& armorIncreasing)
{
	for (int i = 0; i < slot; i++)
	{
		for (int j = 0; j < capacity / slot; j++)
		{
			if (all[i][j] != nullptr)
			{
				all[i][j]->armorIcreasing(armorIncreasing);
			}
		}
	}
}
