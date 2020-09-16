#pragma once
#include "gameNode.h"
#include "monster.h"
#include "player.h"
class popolScene : public gameNode
{
private:



	player *player2;

	
	RECT cameraPoint1;

	
	monster *m[10];


	int monsterCount = 2;
	vector<monster> monVec;



	int _alpha = 255;


public:

	HRESULT init();
	void release();
	void update();
	void render();




};

