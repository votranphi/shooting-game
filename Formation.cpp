#include "Formation.h"
#include "Flank.h"
#include "Front.h"
#include "LongRange.h"

Formation::Formation() : line(vector<Line*>(4, nullptr))
{
	line[0] = new Flank(true); // Dynamically allocate the left Flank line pointer
	line[1] = new Flank(false); // Dynamically allocate the right Flank line pointer
	line[2] = new Front; // Dynamically allocate the Front line pointer
	line[3] = new LongRange; // Dynamically allocate the Long Range line pointer
}

Formation::~Formation()
{
	//for (int i = 0; i < 4; i++)
	//{
	//	delete line[i];
	//}
}
