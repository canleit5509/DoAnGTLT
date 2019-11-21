#include "StonePile.h"



StonePile::StonePile()
{	
	srand(time(NULL));
	this->stone = rand()%30 + 1;
	this->next = NULL;
}

int StonePile::getStone()
{
	return this->stone;
}


StonePile::~StonePile()
{
}
