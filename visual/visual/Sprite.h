#ifndef SPRITE_H
#define SPRITE_H

#include "../../src/image.h";

class Sprite
{
public:
	Sprite();
	Sprite(const char* filename);
	void setId(int _id);
	int getId();
	void setType(int t);
	int getType();
	void setPos(Vector2 _pos);
	Vector2 getPos();

	//Sprite(const char* filename, int posX,int posY);
	//~Sprite();

	Image currentsprite;
	int id;
	int type;
	//Used for foods
	Vector2 pos;
};

#endif

