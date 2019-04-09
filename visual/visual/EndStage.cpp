#include "EndStage.h"

Image frame_Buffer_final;

EndStage::EndStage(const char * filename,std::string sound)
{
	frame_Buffer_final.loadTGA(filename);
	Game::instance->theme->stop();
	Game::instance->synth.playSample(sound, 5.0, false);
}

void EndStage::render() const
{
}

void EndStage::update(double elapsed_time, double time) const
{
}

Image EndStage::getFrameBuffer() const
{
	return frame_Buffer_final;
}

int EndStage::getType() const
{
	return 3;
}

void EndStage::renderHeader() const
{
}

std::string EndStage::getPlayerPosition() const
{
	return std::string();
}

void EndStage::updatePlayerPosition(double time_elapsed, Vector2 dir, int facing) const
{
}

void EndStage::updateCameraPoistion() const
{
}

void EndStage::medMode() const
{
}

void EndStage::pickItem() const
{
}
