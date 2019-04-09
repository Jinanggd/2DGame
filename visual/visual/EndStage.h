#ifndef ENDSTAGE_H
#define ENDSTAGE_H

#include "Stage.h"
#include "../../src/game.h"
class EndStage :public Stage
{
public:
	EndStage(const char* filename, std::string sound);

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
