#pragma once
#include "gameNode.h"
#include "monster.h"
#include "player.h"
class stage2 : public gameNode
{




private:
	RECT itemBack[10];

	monster *m[3];
	image* coinImg;
	vector<monster> monVec;

	int monsterCount = 0;


	int renderScoreHelpX = 0;
	int renderScoreHelpY = 0;

	int coinState = 0;
	int _alpha = 255;
	char str[128];

public:
	HRESULT init();
	void release();
	void update();
	void render();


};

