#pragma once
#include "singletonBase.h"
class stageManager :public singletonBase<stageManager>
{
	/*
		stageManager�� �����ؾ��� ��

		�� �������� �ʵ忡 �ѷ����� ������ ����

		�� ���������� ���� ����

	*/


};

class fItem
{
	//�������� ��ġ ����
	RECT stageItem[10];
	//�����۵��� ��� �ִ� ����
	vector<string> stageItemVec;




	//���Ͱ� ��Ҵ��� �׾����� ����
	bool monsterAlive[10];
	//������ ��ġ x, y������ setLocation�Լ� �̿��ؼ� ���� ����
	POINT mLocation;
	//���Ͱ� �� ��������
	int monsterCount;
};