#pragma once
#include "singletonBase.h"
class stageManager :public singletonBase<stageManager>
{
	/*
		stageManager가 관리해야할 것

		각 스테이지 필드에 뿌려지는 아이템 정보

		각 스테이지의 몬스터 정보

	*/


};

class fItem
{
	//아이템의 위치 정보
	RECT stageItem[10];
	//아이템들이 담겨 있는 벡터
	vector<string> stageItemVec;




	//몬스터가 살았는지 죽었는지 정보
	bool monsterAlive[10];
	//몬스터의 위치 x, y값으로 setLocation함수 이용해서 설정 가능
	POINT mLocation;
	//몬스터가 몇 마리인지
	int monsterCount;
};