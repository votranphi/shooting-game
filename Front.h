#pragma once
#include "Line.h"

class Front : public Line
{
public:
	Front();

	void arrange(vector<Army*>&);
};