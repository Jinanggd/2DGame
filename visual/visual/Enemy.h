#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "../../src/framework.h"
#include "Player.h"
class Enemy
{
public:
	Enemy();
	//~Enemy();
	void render();
	void update(double elapsed_time, double time);
	void inVisionArea();

	void towardsPlayer();
	void setRandomDirection();

	Sprite* sprite;
	Vector2 directions[4] = { Vector2(1,0), Vector2(-1,0), Vector2(0,1), Vector2(0,-1) };
	Vector2 position;
	Vector2 direction;
	float vision = 60.0f;
	int velocity = 40;


};

#endif

