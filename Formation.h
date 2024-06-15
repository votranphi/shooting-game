#pragma once
#include "Line.h"

class Formation
{
	vector<Line*> line;

public:
	Formation();

	friend class Game;

	~Formation();
};