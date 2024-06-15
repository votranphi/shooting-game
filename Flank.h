#pragma once
#include "Line.h"

class Flank : public Line
{
	bool isLeft;

public:
	Flank(const bool& isLeft); // b

	void arrange(vector<Army*> &); // c

	void virtualArmor(const int&);
};