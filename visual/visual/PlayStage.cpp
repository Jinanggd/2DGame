#include "PlayStage.h"
#include "vector"

//Global variables
int MEAT = 0;
int VEGGIE= 1;
int meatnum = 0;
int veggienum = 0;
Player* p;

Image frameBuffer_Play;
Image minifont;
Vector2 camerapos(0, 0);
Vector2 framesize(0, 0);

//Map realated variables
Image bg;
Matrix<int> mapmask;

//Items / elements / Foods
Sprite spm;
Sprite spv;
std::vector<Sprite> *elements;

//Vector of enemies
std::vector<Enemy> *enemies;

PlayStage::PlayStage() : Stage()
{
	frameBuffer_Play.fill(Color(0, 255, 0));
	frameBuffer_Play.drawRectangle(0, 0, 128, 20, Color(0, 0, 0));
}

PlayStage::PlayStage(int w, int h) :Stage() {

	//Load the elements
	spm = Sprite("data/meat16x16.tga");
	spm.setType(MEAT);
	spv = Sprite("data/veggie16x16.tga");
	spv.setType(VEGGIE);
	minifont.loadTGA("data/mini-font-white-4x6.tga"); //load bitmap-font image
	bg.loadTGA("data/bg.tga");

	meatnum = 0;
	veggienum = 0;
	//Start buffer
	frameBuffer_Play.resize(w, h);

	//Init variables ( Player and vectors ) 
	p = new Player();
	elements = new std::vector<Sprite>;
	enemies = new std::vector<Enemy>;

	//Set the position of the camera
	camerapos.x = p->instance->position.x - w / 2;
	camerapos.y = p->instance->position.y - h / 2;
	framesize.x = w;
	framesize.y = h;
	
	//Init / Fill vectors and Matrix
	fillWorldMatrix();
	fillElements();
	SpawnEnemies();

	//First frame
	frameBuffer_Play.fill(Color::BLACK);
	frameBuffer_Play.drawImage(bg, 0, 20);
	renderHeader();
	p->render(&frameBuffer_Play, camerapos);
	
}

void PlayStage::render() const {
	frameBuffer_Play.fill(Color::BLACK);
	frameBuffer_Play.drawImage(bg, 0-camerapos.x, 20-camerapos.y); 
	renderElements();

	p->render(&frameBuffer_Play, camerapos);
	for (int i = 0; i < enemies->size(); i++)
		enemies->at(i).render(&frameBuffer_Play,camerapos);
	
	renderHeader();
}

//Update Function for Player and enemies
void PlayStage::update(double elapsed_time, double time) const {

	for (int i = 0; i < enemies->size(); i++)
		enemies->at(i).update(elapsed_time,time,mapmask);
	p->instance->update(elapsed_time);
	
}

Image PlayStage::getFrameBuffer() const {
	return frameBuffer_Play;
}

int PlayStage::getType() const {
	return 2;
}

//Method to render the header of the game ( The grey topbar ) 
void PlayStage::renderHeader() const
{
	frameBuffer_Play.drawRectangle(0, 0, framesize.x, 20, Color::GRAY); // Gray background
	frameBuffer_Play.drawText("HUNGER BAR", 0, 0, minifont,4,6);
	frameBuffer_Play.drawText("MEAT: "+std::to_string(meatnum)+" VEGGIE: "+std::to_string(veggienum), 50, 0, minifont, 4, 6);
	frameBuffer_Play.drawLine(0, 10, p->instance->staminabar, 10, Color::BLUE);
	frameBuffer_Play.drawLine(0, 11, p->instance->staminabar, 11, Color::BLUE);
	frameBuffer_Play.drawLine(0, 12, p->instance->staminabar, 12, Color::BLUE);
	frameBuffer_Play.drawText(p->instance->getStamina(), 105, 10, minifont,4,6);
	
}

//Helping function to print the position of the user
std::string PlayStage::getPlayerPosition() const
{
	return p->instance->getPostion();
}


//update functions for player and camera called in game 
void PlayStage::updatePlayerPosition(double time_elapsed, Vector2 dir, int facing) const
{
	p->updatePosition(dir, time_elapsed,mapmask,facing);
	updateCameraPoistion();
}

void PlayStage::updateCameraPoistion() const
{
	camerapos.x = p->instance->position.x - framesize.x / 2;
	camerapos.y = p->instance->position.y - framesize.y / 2;
	//applyBoundaries();
}

//Change the user to the meditation mode
void PlayStage::medMode() const
{
	p->instance->changeStage();
}

//Method to apply the boundaries to the camera
//UNFINISHED - Decided  to be uneeded
void PlayStage::applyBoundaries() const
{
	if (camerapos.x < -(bg.width/2) + framesize.x/2)
		camerapos.x = -(bg.width / 2) + framesize.x / 2;
	else if (camerapos.x > bg.width/2 - (framesize.x/2))
		camerapos.x = bg.width / 2 - (framesize.x / 2);
	else if (camerapos.y <-(bg.height/2) +framesize.y/2)
		camerapos.y = -(bg.height / 2) + framesize.y / 2;
	else if (camerapos.y >bg.height/2 -  (framesize.y/2))
		camerapos.y = bg.height / 2 - (framesize.y / 2);
}

//Parse the information from the bg_mask
void PlayStage::fillWorldMatrix() const
{
	Image mask;
	mask.loadTGA("data/bg_mask.tga");
	mapmask.resize(mask.width, mask.height);

	for (int i = 0; i < mask.width; i++)
		for (int j = 0; j < mask.height; j++) {
			if (mask.getPixel(i, j) == Color::BLACK) //Pixels that can be walked
				mapmask.set(i, j, 0);
			else if (mask.getPixel(i, j) == Color::WHITE) //Wall
				mapmask.set(i, j, 1);
			else if (mask.getPixel(i, j) == Color::GREEN) //Veggies
				mapmask.set(i, j, 2);
			else if (mask.getPixel(i, j) == Color::RED) //Meat
				mapmask.set(i, j, 3);
			else if (mask.getPixel(i, j) == Color::BLUE) //Enemy starting position
				mapmask.set(i, j, 4);
		}
}

//Generate the food items and store them into the elements vector
void PlayStage::fillElements() const
{
	int id = 0;
	for (int i = 0; i < mapmask.width; i++) {
		for (int j = 0; j < mapmask.height; j++) {
			if (mapmask.get(i, j) == 3) {
				spm.setId(id);
				spm.setPos(Vector2(i, j));
				id++;
				meatnum++;
				elements->push_back(spm);
			}
			else if (mapmask.get(i, j) == 2) {
				spv.setId(id);
				spv.setPos(Vector2(i, j));
				id++;
				veggienum++;
				elements->push_back(spv);
			}
		}
	}
}

void PlayStage::renderElements() const
{
	for (int i = 0; i < elements->size(); i++) {
		frameBuffer_Play.drawImage(elements->at(i).currentsprite, elements->at(i).pos.x - camerapos.x, elements->at(i).pos.y - camerapos.y);
	}
}

//Update the number of elements
void PlayStage::updateElements() const
{
	meatnum = 0;
	veggienum = 0;
	for (int i= 0; i < elements->size(); i++) {
		if (elements->at(i).getType() == 0) meatnum++;
		else veggienum++;
	}
}

//Check if there is no food in the game - if it is 0, the player wins
void PlayStage::checkGameOver() const
{
	if (meatnum == 0) {
		//Player Win
		Game::instance->endGame("data/Youwin.tga");
	}
}

void PlayStage::SpawnEnemies() const
{
	for (int i = 0; i < mapmask.width; i++) {
		for (int j = 0; j < mapmask.height; j++) {
			if (mapmask.get(i, j) == 4) {
				Enemy e(Vector2(i, j));
				enemies->push_back(e);
			}
		}
	}
}

void PlayStage::pickItem() const
{
	p->pickFood(mapmask, elements);
	updateElements();
	checkGameOver();
}


