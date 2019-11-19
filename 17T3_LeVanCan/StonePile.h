#pragma once
#include <random>
#include <time.h>
const int MAXSTONE = 30;
class StonePile
{
	int stone;
	StonePile * next;
public:
	StonePile();
	int getStone();
	~StonePile();
};

