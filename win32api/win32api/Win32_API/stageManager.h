#pragma once
#include "singletonBase.h"
#include "fInfo.h"
class stageManager :public singletonBase<stageManager>
{
	/*
		stageManager�� �����ؾ��� ��

		�� �������� �ʵ忡 �ѷ����� ������ ����

		�� ���������� ���� ����

	*/
public:
	fInfo *stageOne;

	fInfo *stageTwo;

	fInfo *stageThr;

	vector<string> useItemVec;

public:
	void stageOneInit();
	void stageTwoInit();
	void stageThrInit();
};

