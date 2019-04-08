#ifndef STAGE_H
#define STAGE_H

#include "../../src/image.h";

//Stage abstract class
class Stage
{
public:
	Stage();

	//Member Functions 
	//Basics functions for every stage ( Renders, update and stage type ) 
	virtual void render() const = 0;
	virtual void update(double elapsed_time, double time) const = 0;
	virtual Image getFrameBuffer() const = 0;
	virtual int getType() const = 0;
	virtual void renderHeader()const = 0;
	

	//Functions for PlayStage
	virtual void updatePlayerPosition(double time_elapsed, Vector2 dir, int facing) const = 0;
	virtual void updateCameraPoistion() const = 0;
	virtual std::string getPlayerPosition() const = 0;
	virtual void medMode()const = 0;
	virtual void pickItem() const = 0;

	
};


#endif 