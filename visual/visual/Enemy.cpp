#include "Enemy.h"



Enemy::Enemy()
{

}


//Update the enemy position
void Enemy::update(double elapsed_time, double time)
{
	if (int(time) % 5 == 0)
		towardsPlayer();
	else
		setRandomDirection();

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


