#include "setDefine.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init(TRUE);

	

	//popol
	SCENEMANAGER->addScene("포폴", new popolScene);

	SCENEMANAGER->addScene("포폴2", new stage2);

	playerS->playerInit();
	STAGEMANAGER->stageOneInit();



	//====================================
	//재생할 사운드를 추가
	SOUNDMANAGER->addSound("브금", "BGM.mp3",true,true);

	//사운드 재생
	//SOUNDMANAGER->play("브금", 0.5f);

	//============임시================================
	IMAGEMANAGER->addImage("뒷배경1", "Images/bakcground_day1.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒷배경2", "Images/bakcground_day2.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒷배경3", "Images/bakcground_day3.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("배경3", "Images/first_p.bmp", 0, 0, 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경3_c", "Images/first_c.bmp", 0, 0, 1312, 768, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("체력", "Images/life.bmp", 27 * 2, 35 * 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("itemBack", "Images/invenBack.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("food", "Images/food.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포도", "Images/포도.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("물고기", "Images/물고기.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("t6", "Images/t6.bmp", 100, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("화살표", "Images/arrow.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("화살표", "Images/arrow.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1coin", "Images/justCoin.bmp", 25, 25, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("coin", "Images/coin.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	//============임시================================






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
		SCENEMANAGER->changeScene("포폴");

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		SCENEMANAGER->changeScene("포폴2");

}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	//render
	SCENEMANAGER->render();

	this->getBackBuffer()->render(getHDC());
}
