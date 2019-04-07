#ifndef PLAYSTAGE_H
#define PLAYSTAGE_H

#include "Stage.h"
#include "Player.h"
#include "../../src/game.h"

class PlayStage : public Stage
{
public:
	PlayStage();
	PlayStage(int w, int h);
	//~PlayStage();



	virtual void render() const;
	virtual void update() const;
	virtual Image getFrameBuffer() const;
	virtual int getType() const;
	virtual void renderHeader()const;
	virtual std::string getPlayerPosition() const;


	virtual void updatePlayerPosition(double time_elapsed, Vector2 dir, int facing) const;
	virtual void updateCameraPoistion() const;
	virtual void medMode()const;

	void applyBoundaries() const;
	void fillWorldMatrix() const;

	Player* p;

};

#endif

