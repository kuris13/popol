#pragma once
#include "setDefine.h"
class monster
{

public:

	image* monsterImg;
	image Img;

	RECT *playerRect;


	string backName = "";

	//몬스터의 초기 좌표
	int x, y;

	//몬스터의 이전 프레임에서의 높이
	int bHeight = 0;

	//몬스터의 상태 
	int state = 0;

	//몬스터의 애니메이션 진행 상태
	int idleState = 0;
	int runState = 0;
	int attackState = 0;
	int hitState = 0;
	int deathState = 0;

	int monLife =4;
	int ste = 0;
	//몬스터의 랜딩 상태 
	int landing = 1;

	//몬스터의 이전 프레임에서의 x값
	int bFrameLeft = 0;
	int bFreameRight = 0;

	//현재 몬스터의 방향
	int dy = 0;

	//몬스터의 상태
	bool attackOn = false;
	bool jumpOn = false;
	bool hitOn = false;
	bool floorOn = false;
	bool floorCheck = false;
	bool steMode = false;
	bool coll = false;
	bool deathOn= false;

	RECT mRc;

	void monsterInit();
	void monsterMoveMent();
	void setLocation(int x, int y);

};
