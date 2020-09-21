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
	
	//필드 아이템 이름 
	RECT stageItem[10];
	//필드 아이템 종류
	vector<string> fieldVec{ "체력","food","포도","물고기" };

	
	vector<monster> monVec;
	int monsterCount = 2;


	int _alpha = 255;
	char str[128];

public:

	HRESULT init();
	void release();
	void update();
	void render();




};

