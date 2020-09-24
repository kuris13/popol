#pragma once
#include "setDefine.h"
class monster
{

public:

	image* monsterImg;
	image Img;

	RECT *playerRect;


	string backName = "";

	//������ �ʱ� ��ǥ
	int x, y;

	//������ ���� �����ӿ����� ����
	int bHeight = 0;

	//������ ���� 
	int state = 0;

	//������ �ִϸ��̼� ���� ����
	int idleState = 0;
	int runState = 0;
	int attackState = 0;
	int hitState = 0;
	int deathState = 0;

	int monLife =4;
	int ste = 0;
	//������ ���� ���� 
	int landing = 1;

	//������ ���� �����ӿ����� x��
	int bFrameLeft = 0;
	int bFreameRight = 0;

	//���� ������ ����
	int dy = 0;

	//������ ����
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
