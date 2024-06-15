#include "Front.h"
#include <stack>

Front::Front() : Line(CAPACITY_OF_FRONT, SLOT_OF_FRONT)
{

}

void Front::arrange(vector<Army*>& group)
{
	// Store all the soldiers in the group to a stack in order: Spear, Sword, Hop
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
	for (int i = 0; i < group.size(); i++)
	{
		if (group[i]->getType() == hop)
		{
			groupStack.push(group[i]);
		}
	}

	// Arrange the soldiers in the stack to the Front line
	for (int i = 0; i < slot; i++)
	{
		bool isHopInSlot = false;
		bool isSwordInSlot = false;
		int j;
		for (j = 0; j < capacity / slot && all[i][j] != nullptr; j++)
		{
			if (all[i][j]->getType() == hop)
			{
				isHopInSlot = true;
			}
			else if (all[i][j]->getType() == sword)
			{
				isSwordInSlot = true;
			}
		}

		if (j < capacity / slot)
		{
			if (isHopInSlot)
			{
				while (j < capacity / slot && !groupStack.empty() && groupStack.top()->getType() == hop)
				{
					all[i][j++] = groupStack.top();
					groupStack.pop();
				}
			}
			else if (isSwordInSlot)
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
