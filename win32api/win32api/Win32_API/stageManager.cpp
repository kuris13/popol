#include "stageManager.h"
#include "setDefine.h"

void stageManager::stageOneInit()
{
	//�ε������� ó��
	stageOne = new fInfo();
	

	stageOne->stageItemVec.push_back("ü��");
	stageOne->stageItemVec.push_back("food");
	stageOne->stageItemVec.push_back("����");
	stageOne->stageItemVec.push_back("�����");

	//ü��
	stageOne->stageItem[0] = RectMake(870, 300, 100, 100);

	//food
	stageOne->stageItem[1] = RectMake(800, 500, 100, 100);

	//����
	stageOne->stageItem[2] = RectMake(615, 520, 100, 100);
	
	//�����
	stageOne->stageItem[3] = RectMake(380, 365, 100, 100);

	stageOne->coin = 1;
	stageOne->coinRect[0] = RectMake(700, 350, 50,50);


}

void stageManager::stageTwoInit()
{
	//�ε������� ó��
	stageTwo = new fInfo();


	stageTwo->coin = 5;
	stageTwo->coinRect[0] = RectMake(580, 110, 50, 50);
	stageTwo->coinRect[1] = RectMake(740, 170, 50, 50);
	stageTwo->coinRect[2] = RectMake(900, 240, 50, 50);
	stageTwo->coinRect[3] = RectMake(1060, 300, 50, 50);
	stageTwo->coinRect[4] = RectMake(400, 600, 50, 50);


}

void stageManager::stageThrInit()
{
	//�ε������� ó��
	stageThr = new fInfo();


	stageThr->coin = 7;
	stageThr->coinRect[0] = RectMake(200, 400, 50, 50);
	stageThr->coinRect[1] = RectMake(300, 580, 50, 50);
	stageThr->coinRect[2] = RectMake(400, 580, 50, 50);
	stageThr->coinRect[3] = RectMake(500, 580, 50, 50);
	stageThr->coinRect[4] = RectMake(600, 580, 50, 50);

	stageThr->coinRect[5] = RectMake(1120, 200, 50, 50);
	stageThr->coinRect[6] = RectMake(1200, 200, 50, 50);
}

