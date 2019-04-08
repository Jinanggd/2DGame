#include "StartStage.h"

//Some Globals
Image frameBuffer_Start(128, 128);
Image anim1(128,128);
Image anim2(128, 128);
int curranim1;

StartStage::StartStage() : Stage()
{
	anim1.loadTGA("data/Start1.tga");
	anim2.loadTGA("data/Start2.tga");
	curranim1 = 0;
	frameBuffer_Start = anim1;
}

//Changes beetween frame 1 and 2
void StartStage::render() const {

	if (curranim1 % 24 ==0)
		frameBuffer_Start = anim2;
	else if(curranim1 %30 ==0 )
		frameBuffer_Start = anim1;
	
	curranim1++;
}

void StartStage::update(double elapsed_time, double time) const{

}

Image StartStage::getFrameBuffer() const {
	return frameBuffer_Start;
}

int StartStage::getType() const {
	return 0;
}

//Non-used functions 
void StartStage::renderHeader() const
{
}

std::string StartStage::getPlayerPosition() const
{
	return std::string();
}


void StartStage::updatePlayerPosition(double time_elapsed, Vector2 dir, int facing) const
{
}

void StartStage::updateCameraPoistion() const {

}

void StartStage::medMode() const
{
}

void StartStage::pickItem() const
{
}
