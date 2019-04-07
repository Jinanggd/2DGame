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

void Player::update()
{
	f_ox += 0.25;
	sporientationx = (int(f_ox) % 4);
	if(medidating) staminabar -= 0.10f;
}

void Player::changeStage()
{
	medidating = !medidating;
	if (medidating) sporientationy = 4;
	else sporientationy = 0;
}

void Player::updatePosition(Vector2 dir, double elapsed_time,Matrix<int> map,int facing)
{
	if (!medidating) {
		sporientationy = facing;
		Vector2 newpos;
		newpos = position + dir * (velocity*elapsed_time);
		switch (map.get(int(newpos.x), int(newpos.y)))
		{
			case 0: // Black zone means we can walk in there
				if (isInsideSprite(newpos, map, 0))
					position = newpos;
				break;
			case 1: // White zone means we cannot walk in there ( we won't update the position ) 
				break;
			case 2: // Vegetables - Substract player stamina
				break;
			case 3: // Meat - Add player stamina
				break;
			case 4: // Enemy - Substract player life
				break;
		}
	}
		

}

//PENDING
bool Player::isInsideSprite(Vector2 v, Matrix<int> map, int value)
{
	if (map.get(int(v.x + 14), int(v.y - 18)) == value)
		return true;
	return false;
}

std::string Player::getPostion() {
	return position.toString();
}

std::string Player::getStamina()
{
	return std::to_string(staminabar);
}

std::string Player::getLifes()
{
	return std::to_string(lifes);
}

void Player::substractLife()
{
	lifes--;
}




