#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "../../src/framework.h"
#include "Player.h"
#include "../../src/game.h"
#include "../../src/synth.h"

class Enemy
{
public:
	Enemy(Vector2 pos);
	Enemy(Vector2 pos, Image sp, Image bbsp); //Does not work properly - PENDING

	void render(Image* framebuffer, Vector2 campos);
	void update(double elapsed_time, double time, Matrix<int>map);
	bool inVisionArea();

	void towardsPlayer();
	void setInverseDirection();
	void directionToSpriteAnim();
	bool isInsideSprite(Vector2 v, Matrix<int>map, int value);

	Sprite* sprite;
	Vector2 directions[4] = { Vector2(1,0), Vector2(-1,0), Vector2(0,1), Vector2(0,-1) };
	Vector2 position;
	Vector2 direction;
	int sporientationy = 0;
	int sporientationx = 0;
	float f_ox = 0.0f;
	float vision = 30.0f;
	int velocity = 10;
	bool locked = false;

	Synth audio;


};
#endif

