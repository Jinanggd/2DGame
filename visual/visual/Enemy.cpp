#include "Enemy.h"

Image buble;

Enemy::Enemy(Vector2 pos)
{
	position = pos;
	sprite = new Sprite("data/Master.tga");
	buble.loadTGA("data/Bubble16x16.tga");
	direction = directions[rand() % 4];
}

//Does not work properly - PENDING TO ASK
Enemy::Enemy(Vector2 pos, Image sp, Image bbsp)
{
	position = pos;
	sprite->currentsprite.Get("data/Bubble16x16.tga");
	buble.Get("data/Bubble16x16.tga");
	direction = directions[rand()%4];
}

void Enemy::render(Image * framebuffer, Vector2 campos)
{
	framebuffer->drawImage(sprite->currentsprite, ceil(position.x - campos.x), ceil(position.y - campos.y),
		Area(sporientationx * 14, sporientationy * 18, 14, 18));
	if (locked) {
		framebuffer->drawImage(buble,ceil(position.x-campos.x),ceil(position.y-campos.y-15));
	}
}

//Update the enemy position
void Enemy::update(double elapsed_time, double time, Matrix<int> map)
{
	if (!locked) {
		//Every five seconds the enemy will change the direction towards the player
		if (int(time) % 5 == 0)
			towardsPlayer();

		//For animation purposes ( update the sporientationy )
		directionToSpriteAnim();
		//Animation
		f_ox += elapsed_time * 3;
		sporientationx = (int(f_ox) % 4);

		//New position for the enemy
		Vector2 Newpos = position + direction * elapsed_time*velocity;
		if (!isInsideSprite(Newpos, map, 1))
			position = Newpos;
		if (inVisionArea()) {
			//std::cout << "Spotted";
			//Shut down the game
		}
			
	}
	else if(int(time)%7 ==0){
		locked = false;
		setInverseDirection();
	}
	
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

void Enemy::setInverseDirection()
{
	direction *= -1;
}

void Enemy::directionToSpriteAnim()
{
	if (direction == directions[0])
		sporientationy = 1;
	else if (direction == directions[1])
		sporientationy = 2;
	else if (direction == directions[2])
		sporientationy = 0;
	else 
		sporientationy = 3;
}

bool Enemy::isInsideSprite(Vector2 v, Matrix<int> map, int value)
{
	for(int i = int(v.x); i < v.x + 14; i++) {
		if (i<0 || i>map.width) continue;
		for (int j = int(v.y) - 20; j < v.y; j++) {
			if (j<0 || j>map.height) continue;
			if (map.get(i, j) == value)
				return true;
		}
	}
	return false;
}

bool Enemy::inVisionArea()
{
	Vector2 p_position = Player::instance->position;
	Vector2 vectorEP = p_position - position;
	vectorEP = vectorEP.normalize();
	float length = position.distance(p_position);
	float dot = vectorEP.dot(direction);

	if (length < vision && dot > 0 && !Player::instance->medidating) {
		Player::instance->addStamina(-10.0f);
		locked = true;

		return true;
		//Player::instance->substractLife();
	}

	return false;
}


