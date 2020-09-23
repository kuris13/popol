#pragma once
#include "gameNode.h"
#include "monster.h"
#include "player.h"
class popolScene : public gameNode
{
private:

	POINT CAMERA = { 0,0 };

	player *player2;

	RECT itemBack[10];
	
	monster *m[2];
	image* coinImg;
	vector<monster> monVec;
	int monsterCount = 2;

	int score = 0;

	int renderScoreHelpX = 0;
	int renderScoreHelpY = 0;

	int coinState=0;
	int _alpha = 255;
	char str[128];



public:

	HRESULT init();
	void release();
	void update();
	void render();




};

