#include "PlayStage.h"
#include "vector"
int MEAT = 0;
int VEGGIE= 1;
int meatnum = 0;
int veggienum = 0;
//Global variables
Image frameBuffer_Play;
Image minifont;
Vector2 camerapos(0, 0);
Vector2 framesize(0, 0);

//Map
Image bg;
Matrix<int> mapmask;
Sprite spm;
Sprite spv;
std::vector<Sprite> *elements;
std::vector<Enemy> *enemies;

//Depracated - Pending to be eliminated
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

	//Create the player
	p = new Player();
	elements = new std::vector<Sprite>;
	enemies = new std::vector<Enemy>;
	//Set the position of the camera
	camerapos.x = p->instance->position.x - w / 2;
	camerapos.y = p->instance->position.y - h / 2;
	framesize.x = w;
	framesize.y = h;
	
	fillWorldMatrix(); // Init the matrix world 
	fillElements();
	SpawnEnemies();

	frameBuffer_Play.fill(Color::BLACK);
	frameBuffer_Play.drawImage(bg, 0, 20);
	renderHeader();
	p->render(&frameBuffer_Play, camerapos);
	
}

void PlayStage::render() const {
	frameBuffer_Play.fill(Color::BLACK);
	frameBuffer_Play.drawImage(bg, 0-camerapos.x, 20-camerapos.y); // 0,0 will be the center of the image
	renderElements();
	renderHeader();


	for (int i = 0; i < enemies->size(); i++)
		enemies->at(i).render(&frameBuffer_Play,camerapos);
	p->render(&frameBuffer_Play, camerapos);
}

void PlayStage::update(double elapsed_time, double time) const {

	for (int i = 0; i < enemies->size(); i++)
		enemies->at(i).update(elapsed_time,time);
	p->instance->update(elapsed_time);
	
}

Image PlayStage::getFrameBuffer() const {
	return frameBuffer_Play;
}

int PlayStage::getType() const {
	return 2;
}

//Method to render the header of the game ( The grey topbar with life and stamina ) 
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

std::string PlayStage::getPlayerPosition() const
{
	return p->instance->getPostion();
}


//update functions for player and camera
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

void PlayStage::medMode() const
{
	p->instance->changeStage();
}


//Method to apply the boundaries to the camera (?) - UNFINISHED
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

void PlayStage::fillWorldMatrix() const
{
	Image mask;
	mask.loadTGA("data/bg_mask.tga");
	mapmask.resize(mask.width, mask.height);

	for (int i = 0; i < mask.width; i++)
		for (int j = 0; j < mask.height; j++) {
			if (mask.getPixel(i, j) == Color::BLACK)
				mapmask.set(i, j, 0);
			else if (mask.getPixel(i, j) == Color::WHITE)
				mapmask.set(i, j, 1);
			else if (mask.getPixel(i, j) == Color::GREEN)
				mapmask.set(i, j, 2);
			else if (mask.getPixel(i, j) == Color::RED)
				mapmask.set(i, j, 3);
			else if (mask.getPixel(i, j) == Color::BLUE)
				mapmask.set(i, j, 4);
		}
}

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

void PlayStage::updateElements() const
{
	meatnum = 0;
	veggienum = 0;
	for (int i= 0; i < elements->size(); i++) {
		if (elements->at(i).getType() == 0) meatnum++;
		else veggienum++;
	}
}

void PlayStage::checkGameOver() const
{
	if (meatnum == 0) {
		//Player Win
	}
	else if (p->instance->staminabar == 0.0f) {
		//GameOver
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


