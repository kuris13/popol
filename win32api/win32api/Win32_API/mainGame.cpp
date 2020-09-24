#include "setDefine.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init(TRUE);

	

	//popol
	SCENEMANAGER->addScene("����", new popolScene);

	SCENEMANAGER->addScene("����2", new stage2);

	



	//====================================
	//����� ���带 �߰�
	SOUNDMANAGER->addSound("���", "BGM.mp3",true,true);

	//���� ���
	//SOUNDMANAGER->play("���", 0.5f);

	//============�ӽ�================================
	IMAGEMANAGER->addImage("�޹��1", "Images/bakcground_day1.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��2", "Images/bakcground_day2.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��3", "Images/bakcground_day3.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("main", "Images/main.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���3", "Images/first_p.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���3_c", "Images/first_c.bmp", 1312, 768, true, RGB(255, 0, 255));


	//������
	IMAGEMANAGER->addFrameImage("coin", "Images/coin.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü��", "Images/life.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("itemBack", "Images/invenBack.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("food", "Images/food.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/����.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����", "Images/�����.bmp", 56, 56, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("t6", "Images/t6.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ȭ��ǥ", "Images/arrow.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1coin", "Images/justCoin.bmp", 25, 25, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addFrameImage("skel_idle", "Images/skel/idle.bmp", 1144, 128, 11, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_attack", "Images/skel/attack.bmp", 1872, 148, 18, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_death", "Images/skel/death.bmp", 1560, 128, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_walk", "Images/skel/walk.bmp", 1352, 128, 13, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_hit", "Images/skel/hit.bmp", 832, 128, 8, 2, true, RGB(255, 0, 255));


	//�÷��̾�
	IMAGEMANAGER->addFrameImage("p_idle", "Images/player/idle.bmp", 1800, 120, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_run", "Images/player/run.bmp", 960, 120, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_attack", "Images/player/attack.bmp",2640, 130, 22, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_roll", "Images/player/roll.bmp",1800, 120, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_jump", "Images/player/jump.bmp",600, 124, 5, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_fall", "Images/player/fall.bmp", 240, 124, 2, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_hit", "Images/player/landing.bmp", 240, 124, 2, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_death", "Images/player/death.bmp", 1800, 120, 15, 2, true, RGB(255, 0, 255));



	//============�ӽ�================================



	playerS->playerInit();

	STAGEMANAGER->stageOneInit();
	STAGEMANAGER->stageTwoInit();
	STAGEMANAGER->stageThrInit();


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

	if (A == 40) A = 0;
	if (loadingIMG == WINSIZE_X/2) loadingOn = true;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		SCENEMANAGER->changeScene("����");


}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);


	IMAGEMANAGER->render("main", getMemDC());

	IMAGEMANAGER->findImage("p_run")->setFrameX(A++/5);



	if (!loadingOn)
	{
		IMAGEMANAGER->frameRender("p_run", getMemDC(), ++loadingIMG, WINSIZE_Y * 3 / 4);
	}
	else {
		IMAGEMANAGER->frameRender("p_run", getMemDC(), loadingIMG, WINSIZE_Y * 3 / 4);
	}

	//render
	SCENEMANAGER->render();

	this->getBackBuffer()->render(getHDC());
}
