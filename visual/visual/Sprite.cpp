#include "Sprite.h"



Sprite::Sprite()
{
}

Sprite::Sprite(const char* filename) {
	currentsprite.loadTGA(filename);
}

void Sprite::setId(int _id)
{
	id = _id;
}

int Sprite::getId()
{
	return id;
}

void Sprite::setType(int t)
{
	type = t;
}

int Sprite::getType()
{
	return type;
}

void Sprite::setPos(Vector2 _pos)
{
	pos = _pos;
}

Vector2 Sprite::getPos()
{
	return pos;
}

