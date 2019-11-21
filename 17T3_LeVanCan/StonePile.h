#pragma once
#include <random>
#include <time.h>
const int MAXSTONE = 30;
class StonePile
{
	int stone;
public:
	StonePile * next;
	StonePile();
	int getStone();
	~StonePile();
};

