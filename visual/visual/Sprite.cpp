#include "Sprite.h"



Sprite::Sprite()
{
}

Sprite::Sprite(const char* filename) {
	currentsprite.loadTGA(filename);
}

