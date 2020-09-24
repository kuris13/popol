#pragma once
#include "singletonBase.h"
class player : public singletonBase<player>
{

private :

	int asb;
public:
	image* playerImg;

	RECT rc;
	RECT rc2;

	vector<string> haveitem;
	vector<string> invenVec2;

	int score = 0;
	int nowScene = 1;
	int monstCount = 0;
	bool isMonsterAttack[10] = { false };
	RECT mRc[10];

	int CAMERA = 0;
	string backName;

	int _x, _y;

	int _probeY;

	int bHeight = 0;
	int state = 0;
	int idleState = 0;
	int runState = 0;
	int attackState = 0;
	int jumpState = 0;
	int rollState = 0;
	int fallState = 0;
	int hitState = 0;
	int deathState = 0;

	int cameraState = 0;

	int hitMonNum = 0;

	int landing = 1;

	int _alpha = 255;


	int bFrameLeft = 0;
	int bFreameRight = 0;

	int jumpGa = 0;
	int maxJump = 150;
	int jumpSpeed = 20;
	int fallGa = 0;
	int noHitGa = 0;
	int runSpeed = 5;
	int rollSpeed =5;

	int dy = 0;
	char str[128];
	bool attackOn = false;
	bool jumpOn = false;
	bool rollOn = false;
	bool floorOn = false;
	bool fallOn = false;
	bool hitOn = false;
	bool floorCheck = false;
	bool coll = false;
	bool deathOn = false;
	bool noHitMode = false;

	int lifeCount = 0;

public:
	void playerMovement();
	void playerInit();
	void useItem();
};

