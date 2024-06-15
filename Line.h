#pragma once
#include <vector>
using namespace std;
#include "Army.h"

#define CAPACITY_OF_FLANK 60
#define SLOT_OF_FLANK 3

#define CAPACITY_OF_FRONT 240
#define SLOT_OF_FRONT 8

#define CAPACITY_OF_LONGRANGE 96
#define SLOT_OF_LONGRANGE 8

class Line
{
protected:
	int capacity;
	int slot;
	vector<vector<Army*>> all;

public:
	Line();
	Line(const int&, const int&);

	virtual void arrange(vector<Army*>&) = 0;

	int armyCounting(); // Count number of soldiers in a line

	int armyCounting(const int&); // Count number of soldiers in a slot of the line

	virtual void virtualArmor(const int&) {} // Increase the armor of soldiers in two Flanks

	void beAttacked(Line*);

	bool isEmpty();

	friend class Game;

	~Line();
};