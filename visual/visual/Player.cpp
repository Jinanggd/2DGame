#include "Player.h"

Player* Player::instance = NULL;

Player::Player()
{
	sprite = new Sprite("data/Monk.tga");
	instance = this;
	position.x = 20;
	position.y = 40;
}

void Player::render(Image * framebuffer,Vector2 campos)
{
	framebuffer->drawImage(sprite->currentsprite, ceil(position.x-campos.x),ceil( position.y-campos.y), 
		Area(sporientationx*14, sporientationy*18, 14, 18));
}

void Player::update(double elapsed_time)
{
	f_ox += elapsed_time*3;
	sporientationx = (int(f_ox) % 4);
	if(medidating) addStamina(-0.1f);
}

void Player::changeStage()
{
	medidating = !medidating;
	if (medidating) sporientationy = 4;
	else sporientationy = 0;
}

void Player::updatePosition(Vector2 dir, double elapsed_time,Matrix<int> map,int facing)
{
	//If the Player is medidating, then you cannot move
	if (!medidating) {
		sporientationy = facing;
		Vector2 newpos;
		newpos = position + dir * (velocity*elapsed_time);
		if (!isInsideSprite(newpos, map, 1))
			position = newpos;
	}
}

//Check where exactly is the position at
bool Player::isInsideSprite(Vector2 v, Matrix<int> map, int value)
{
	for (int i = int(v.x); i < v.x + 14; i++) {
		if (i<0 || i>map.width) continue;
		for (int j = int(v.y)-20 ; j < v.y; j++) {
			if (j<0 || j>map.height) continue;
			if (map.get(i, j) == value)
				return true;
		}
	}
	return false;
}

//Depending on the type of food the user picks it can either add stamina or substract stamina
void Player::pickFood(Matrix<int> map, std::vector<Sprite> *element1)
{
	int deleteindex = -1;
	Vector2 foodPos = locateFoodPosition(map);

	std::vector<Sprite> *elements = element1;

	for (int i = 0; i < elements->size(); i++) {
		if (elements->at(i).getPos() == foodPos) {
			if (elements->at(i).getType()==0) {
				addStamina(10.0f);
				/*staminabar += 10;
				if (staminabar >= 100.0f) staminabar = 100.0f;*/
				deleteindex = i;
				break;
			}
			else if (elements->at(i).getType() == 1) {
				addStamina(-10.0f);
				/*staminabar -= 10;
				if (staminabar <= 0.0f) staminabar = 0.0;*/
				deleteindex = i;
				break;
			}
		}
	}

	//Delete it from the vector
	if(deleteindex >-1)
		elements->erase(elements->begin() + deleteindex);
}

void Player::addStamina(float value)
{
	float result = staminabar + value;
	if (result >= 100.0f) staminabar = 100.0f;
	else if (result <= 0.0f) staminabar = 0.0f;
	else
		staminabar = result;
	CheckGameOver();
}

//Checks for the player stamina Bar
void Player::CheckGameOver()
{
	if (staminabar == 0.0f) {
		//GameOver
		Game::instance->endGame("data/Gameover.tga");
	}
}

//Returns the position of the food located
Vector2 Player::locateFoodPosition(Matrix<int> map)
{
	int fx, fy;
	for (int i = position.x - 5; i < position.x + 19; i++) {
		if (i<0 || i>map.width) continue;
		for (int j = position.y -5 ; j < position.y + 21; j++) {
			if (j<0 || j>map.height) continue;
			if (map.get(i, j) == 2 || map.get(i, j) == 3) {
				return Vector2(i, j); // location
			}
		}
	}
	return Vector2(-1,-1);
}

std::string Player::getPostion() {
	return position.toString();
}

std::string Player::getStamina()
{
	return std::to_string(staminabar);
}
