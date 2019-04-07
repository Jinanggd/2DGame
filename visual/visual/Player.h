#ifndef PLAYER_H
#define PLAYER_H

#include "Sprite.h"
#include "../../src/utils.h"

class Player
{
public:
	static Player* instance;
	Player();

	void render(Image* framebuffer, Vector2 campos);
	void updatePosition(Vector2 dir, double elapsed_time, Matrix<int> map,int facing);
	void substractLife();
	void update();
	void changeStage();

	bool isInsideSprite(Vector2 v, Matrix<int>map, int value);
	std::string getPostion();
	std::string getStamina();
	std::string getLifes();


	Vector2 position;
	Sprite* sprite;
	int velocity = 20;
	int sporientationy = 0;
	int sporientationx = 0;
	float f_ox = 0.0f;
	int lifes = 3;
	float staminabar = 100.0f;
	bool medidating = false;
};

#endif