#include "InstructStage.h"

Image frameBuffer_Inst(128, 128);
Image anim3(128, 128);
Image anim4(128, 128);

InstructStage::InstructStage() : Stage()
{
	anim3.loadTGA("data/Ins.tga");
	anim4.loadTGA("data/Ins2.tga");
	frameBuffer_Inst = anim3;
}


void InstructStage::render() const {

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
	if (dir == Vector2(1, 0)) {
		frameBuffer_Inst = anim4;
	}
	if (dir == Vector2(-1, 0)) {
		frameBuffer_Inst = anim3;
	}
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
