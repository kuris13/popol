#pragma once
#include "gameNode.h"
#include "monster.h"
#include "player.h"
class popolScene : public gameNode
{
private:

	POINT CAMERA = { 0,0 };

	player *player2;

	
	RECT cameraPoint1;

	RECT itemBack[10];
	
	monster *m[2];
	
	//필드 아이템 이름 
	RECT stageItem[10];
	//필드 아이템 종류
	vector<string> fieldVec{ "포션 ","물고기","포도","음식" };

	int monsterCount = 2;
	vector<monster> monVec;



	int _alpha = 255;


public:

	HRESULT init();
	void release();
	void update();
	void render();




};

