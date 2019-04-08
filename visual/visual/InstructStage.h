#ifndef INSTRUCTSTAGE_H
#define INSTRUCTSTAGE_H

#include "Stage.h"

//Instruction Stage - The same as StartStage it just shows the instructions of the game
class InstructStage : public Stage
{
public:
	InstructStage();

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

