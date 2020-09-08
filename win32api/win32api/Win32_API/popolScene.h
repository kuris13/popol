#pragma once
#include "gameNode.h"
class popolScene : public gameNode
{
private:
	image* player;
	//플레이어 이미지
	RECT rc;
	//플레이어 충돌체
	RECT rc2;

	RECT foothold[10];


	int state = 0;
	int idleState = 0;
	int runState = 0;
	int attackState = 0;
	int jumpState = 0;
	int rollState = 0;
	int fallState = 0;
	int landing = 1;

	int bFrameLeft = 0;
	int bFreameRight = 0;

	int jumpGa = 0;
	int jumpSpeed = 20;
	int fallGa = 0;


	int dy = 0;
	char str[128];
	char str2[128];
	bool attackOn= false;
	bool jumpOn = false;
	bool rollOn = false;
	bool floorOn = false;
	bool fallOn = false;

public:

	HRESULT init();
	void release();
	void update();
	void render();


};

