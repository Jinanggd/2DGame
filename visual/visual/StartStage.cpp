#include "StartStage.h"


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

//Basic Functions
void StartStage::render() const {

	if (curranim1 % 24 ==0)
		frameBuffer_Start = anim2;
	else if(curranim1 %30 ==0 )
		frameBuffer_Start = anim1;
	
	curranim1++;
}

void StartStage::update() const{

}

Image StartStage::getFrameBuffer() const {
	return frameBuffer_Start;
}

int StartStage::getType() const {
	return 0;
}

void StartStage::renderHeader() const
{
}

std::string StartStage::getPlayerPosition() const
{
	return std::string();
}

//Non-used functions 
void StartStage::updatePlayerPosition(double time_elapsed, Vector2 dir, int facing) const
{
}

void StartStage::updateCameraPoistion() const {

}

void StartStage::medMode() const
{
}
