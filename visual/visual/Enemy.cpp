#include "Enemy.h"


Enemy::Enemy(Vector2 pos)
{
	position = pos;
	sprite = new Sprite("data/Master.tga");
	direction = directions[0];

}

void Enemy::render(Image * framebuffer, Vector2 campos)
{
	framebuffer->drawImage(sprite->currentsprite, ceil(position.x - campos.x), ceil(position.y - campos.y),
		Area(sporientationx * 14, sporientationy * 18, 14, 18));
}

//Update the enemy position
void Enemy::update(double elapsed_time, double time)
{
	if (int(time) % 5 == 0)
		towardsPlayer();
	else
		setRandomDirection();

	directionToSpriteAnim();

	f_ox += elapsed_time*3;
	sporientationx = (int(f_ox) % 4);
	 

	position.x += direction.x*elapsed_time*velocity;
	position.y += direction.y*elapsed_time*velocity;
}

void Enemy::towardsPlayer() {

	//Compute vector from Enemy to the Player
	Vector2 p_position = Player::instance->position;
	Vector2 vectorEP = p_position - position;
	vectorEP = vectorEP.normalize();
	float max = -100000.0f;
	int correctdir_index = 0;

	for (int i = 0; i < 4; i++) {
		if (directions[i].dot(vectorEP) > max) {
			max = directions[i].dot(vectorEP);
			correctdir_index = i;
		}
	}

	//Get the final direction accord to the dot product
	direction = directions[correctdir_index];

}

//Returns a random direction
void Enemy::setRandomDirection()
{
	int random_index = rand() & 3;
	direction = directions[random_index];
}

void Enemy::directionToSpriteAnim()
{
	if (direction == directions[0])
		sporientationy = 1;
	else if (direction == directions[1])
		sporientationy = 2;
	else if (direction == directions[2])
		sporientationy = 3;
	else 
		sporientationy = 0;
}

void Enemy::inVisionArea()
{
	Vector2 p_position = Player::instance->position;
	Vector2 vectorEP = p_position - position;
	vectorEP = vectorEP.normalize();
	float length = position.distance(p_position);
	float dot = vectorEP.dot(direction);

	if (length < vision && dot > 0) {
		Player::instance->substractLife();
	}
}


