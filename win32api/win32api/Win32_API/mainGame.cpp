#include "setDefine.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init(TRUE);

	

	//popol
	SCENEMANAGER->addScene("����", new popolScene);

	SCENEMANAGER->addScene("����2", new stage2);

	playerS->playerInit();
	STAGEMANAGER->stageOneInit();



	//====================================
	//����� ���带 �߰�
	SOUNDMANAGER->addSound("���", "BGM.mp3",true,true);

	//���� ���
	//SOUNDMANAGER->play("���", 0.5f);

	//============�ӽ�================================
	IMAGEMANAGER->addImage("�޹��1", "Images/bakcground_day1.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��2", "Images/bakcground_day2.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��3", "Images/bakcground_day3.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���3", "Images/first_p.bmp", 0, 0, 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���3_c", "Images/first_c.bmp", 0, 0, 1312, 768, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("ü��", "Images/life.bmp", 27 * 2, 35 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("itemBack", "Images/invenBack.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("food", "Images/food.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/����.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����", "Images/�����.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("t6", "Images/t6.bmp", 100, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ȭ��ǥ", "Images/arrow.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ȭ��ǥ", "Images/arrow.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1coin", "Images/justCoin.bmp", 25, 25, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("coin", "Images/coin.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	//============�ӽ�================================






	return S_OK;
}

void mainGame::release()
{
	gameNode::release();


}

void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();


	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		SCENEMANAGER->changeScene("����");

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		SCENEMANAGER->changeScene("����2");

}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	//render
	SCENEMANAGER->render();

	this->getBackBuffer()->render(getHDC());
}
