#ifndef PLAYSTAGE_H
#define PLAYSTAGE_H

#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "../../src/game.h"

class PlayStage : public Stage
{
public:
	PlayStage();
	PlayStage(int w, int h);

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

	//Other utilities functions
	void applyBoundaries() const;
	void fillWorldMatrix() const;
	void fillElements() const;
	void renderElements() const;
	void updateElements() const;
	void checkGameOver() const;
	void SpawnEnemies() const;

	

};

#endif

