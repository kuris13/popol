#pragma once
#include "setDefine.h"
class monster
{
private:

public:

	image* monsterImg;

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
	int fallState = 0;

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
	bool rollOn = false;
	bool floorOn = false;
	bool fallOn = false;
	bool floorCheck = false;
	bool steMode = false;
	bool coll = false;


	RECT mRc;




};
