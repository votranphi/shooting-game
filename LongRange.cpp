#include "LongRange.h"

LongRange::LongRange() : Line(CAPACITY_OF_LONGRANGE, SLOT_OF_LONGRANGE)
{

}

void LongRange::arrange(vector<Army*>& group)
{
	int groupIdx = 0;
	for (int i = 0; i < slot; i++)
	{
		int j;
		for (j = 0; j < capacity / slot && all[i][j] != nullptr; j++)
		{

		}

		while (j < capacity / slot && groupIdx < group.size())
		{
			all[i][j++] = group[groupIdx++];
		}

		if (groupIdx == group.size())
		{
			break;
		}
	}
}
