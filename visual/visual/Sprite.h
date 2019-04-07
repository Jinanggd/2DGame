#ifndef SPRITE_H
#define SPRITE_H

#include "../../src/image.h";

class Sprite
{
public:
	Sprite();
	Sprite(const char* filename);
	//Sprite(const char* filename, int posX,int posY);
	//~Sprite();

	Image currentsprite;
};

#endif

