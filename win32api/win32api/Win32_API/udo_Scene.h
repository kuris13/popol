#pragma once
#include "gameNode.h"

const int MISSILE_MAX{ 128 };
const float FOLLOW{ 60.0F };

typedef struct
{
	float centerX, centerY, speed;
	RECT rc;
}PLAYER;

typedef struct
{
	float startX, startY, centerX, centerY, angle, speed;
	RECT rc;
	bool keepGoing;
}MISSILE;


class udo_Scene : public gameNode
{
private:
	PLAYER _player;
	MISSILE _missile[MISSILE_MAX];



public:

	HRESULT init();
	void release();
	void update();
	void render();

	void missileMovement();


};

