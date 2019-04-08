#ifndef STARTSTAGE_H
#define STARTSTAGE_H

#include "Stage.h"

//Starting stage / scene. Here we just load the welcome menu of the game
class StartStage : public Stage
{
public:
	StartStage();
	
	virtual void render() const;
	virtual void update(double elapsed_time, double time) const;
	virtual Image getFrameBuffer() const;
	virtual int getType() const;
	virtual void renderHeader()const;
	virtual std::string getPlayerPosition() const;

	virtual void updatePlayerPosition(double time_elapsed, Vector2 dir, int facing) const;
	virtual void updateCameraPoistion() const;
	virtual void medMode()const;
	virtual void pickItem() const;

};

#endif

