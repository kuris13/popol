#pragma once
#include "setDefine.h"
class fInfo
{
public:

	//아이템의 위치 정보
	RECT stageItem[10];
	//아이템들이 담겨 있는 벡터
	vector<string> stageItemVec;

	int coin = 1;
	RECT coinRect[10];


};