#include "setDefine.h"
#include "stage2.h"

HRESULT stage2::init()
{
	IMAGEMANAGER->addImage("배경4", "Images/second.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경4_c", "Images/second_c.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("화살표", "Images/arrow.bmp", 40, 40, true, RGB(255, 0, 255));


	//==========================================
	playerS->backName = "배경4_c";
	playerS->playerInit();
	
	playerS->nowScene = 2;
	playerS->rc = RectMake(-30, 100, 60, 60);
	//==========================================
	

	return S_OK;
}

void stage2::release()
{

}

void stage2::update()
{
	playerS->playerMovement();
	if (playerS->rc2.left < 0)
	{
		SCENEMANAGER->changeScene("포폴");
	}
	
}

void stage2::render()
{
	IMAGEMANAGER->render("뒷배경1", getMemDC());
	IMAGEMANAGER->render("뒷배경2", getMemDC());
	IMAGEMANAGER->render("뒷배경3", getMemDC());

	IMAGEMANAGER->render("배경4", getMemDC());



	if (playerS->state == 0)
	{
		IMAGEMANAGER->frameRender("p_idle", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 1)
	{
		IMAGEMANAGER->frameRender("p_run", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 2)
	{
		IMAGEMANAGER->frameRender("p_attack", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 3)
	{
		IMAGEMANAGER->frameRender("p_jump", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 4)
	{
		IMAGEMANAGER->frameRender("p_roll", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 5)
	{
		IMAGEMANAGER->frameRender("p_fall", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 6)
	{
		IMAGEMANAGER->frameRender("p_hit", getMemDC(), playerS->rc.left, playerS->rc.top);
	}


}
