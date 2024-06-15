#pragma once
#include "Line.h"

class LongRange : public Line
{
public:
	LongRange();
	
	void arrange(vector<Army*>&);
};