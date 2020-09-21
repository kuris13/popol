#pragma once
#include "singletonBase.h"
#include "fInfo.h"
class stageManager :public singletonBase<stageManager>
{
	/*
		stageManager가 관리해야할 것

		각 스테이지 필드에 뿌려지는 아이템 정보

		각 스테이지의 몬스터 정보

	*/
public:
	fInfo *stageOne;

	fInfo *stageTwo;

	fInfo *stageThr;

public:
	void stageOneInit();
	void stageTwoInit();
	void stageThrInit();
};

