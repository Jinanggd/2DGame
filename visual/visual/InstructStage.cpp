#include "InstructStage.h"

Image frameBuffer_Inst(128, 128);
Image anim3(128, 128);
Image anim4(128, 128);
int curranim2;

InstructStage::InstructStage() : Stage()
{
	anim3.loadTGA("data/Ins.tga");
	anim4.loadTGA("data/Ins2.tga");
	curranim2 = 0;
	frameBuffer_Inst = anim3;
}


void InstructStage::render() const {

	if (curranim2 %24 == 0 )
		frameBuffer_Inst = anim4;
	else if(curranim2 %30 ==0)
		frameBuffer_Inst = anim3;
	curranim2++;
}

void InstructStage::update(double elapsed_time, double time) const {

}

Image InstructStage::getFrameBuffer() const {
	return frameBuffer_Inst;
}

int InstructStage::getType() const {
	return 1;
}

//Non-used

void InstructStage::renderHeader() const
{
}

std::string InstructStage::getPlayerPosition() const
{
	return std::string();
}

void InstructStage::updatePlayerPosition(double time_elapsed, Vector2 dir, int facing) const
{
}

void InstructStage::updateCameraPoistion() const
{
}

void InstructStage::medMode() const
{
}

void InstructStage::pickItem() const
{
}
