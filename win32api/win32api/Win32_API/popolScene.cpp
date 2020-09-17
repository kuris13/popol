#include "setDefine.h"
#include "popolScene.h"




HRESULT popolScene::init()
{
	//����� ������ �߰��ؾ��� 
	IMAGEMANAGER->addImage("�޹��1", "Images/bakcground_day1.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��2", "Images/bakcground_day2.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��3", "Images/bakcground_day3.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���3", "Images/first_p.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���3_c", "Images/first_c.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ü��", "Images/life.bmp", 27*2, 35*2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ȭ��ǥ", "Images/arrow.bmp", 40 , 40, true, RGB(255, 0, 255));


	cameraPoint1 = RectMake(1250,0,100,WINSIZE_Y);

	//==========================================
	playerS->backName = "���3_c";
	playerS->playerInit();

	player2 = playerS;
	

	//==========================================
	for (int i = 0; i < monsterCount; i++)
	{
		m[i] = new monster();

		m[i]->monsterInit();
		m[i]->playerRect = &player2->rc2;

	}
	m[0]->setLocation(600, 500);
	m[1]->setLocation(1000, 400);
	return S_OK;
}

void popolScene::release()
{
}

void popolScene::update()
{

	player2->playerMovement();

	for (int i = 0; i < monsterCount; i++)
	{
		m[i]->monsterMoveMent();
	}
	

	_alpha -= 3.0f;

	if (_alpha <= 0)
	{
		_alpha = 255;
	}


}

void popolScene::render()
{

	IMAGEMANAGER->render("�޹��1", getMemDC());
	IMAGEMANAGER->render("�޹��2", getMemDC());
	IMAGEMANAGER->render("�޹��3", getMemDC());



	IMAGEMANAGER->render("���3", getMemDC());
	
	/*
	for (int i = 0; i < player2.lifeCount; i++)
	{
		IMAGEMANAGER->render("ü��", getMemDC(),30+i*55,50);
	}


	//RectangleMake(getMemDC(), rc);
	//RectangleMake(getMemDC(), rc2);
	//RectangleMake(getMemDC(), m[0].mRc);

	if (player2.attackOn)
	{
		auto brush = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(getMemDC(), &rc2, brush);
		DeleteObject(brush);
	}
	else if (player2.rollOn)
	{
		auto brush = CreateSolidBrush(RGB(0, 255, 0));
		FillRect(getMemDC(), &rc2, brush);
		DeleteObject(brush);
	}
	*/




	if (player2->state == 0)
	{
		IMAGEMANAGER->frameRender("p_idle", getMemDC(),player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 1)
	{
		IMAGEMANAGER->frameRender("p_run", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 2)
	{
		IMAGEMANAGER->frameRender("p_attack", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 3)
	{
		IMAGEMANAGER->frameRender("p_jump", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 4)
	{
		IMAGEMANAGER->frameRender("p_roll", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 5)
	{
		IMAGEMANAGER->frameRender("p_fall", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 6)
	{
		IMAGEMANAGER->frameRender("p_hit", getMemDC(), player2->rc.left, player2->rc.top);
	}

	
	for (int i = 0; i < monsterCount; i++)
	{
		if (m[i]->state == 0)
		{
			IMAGEMANAGER->frameRender("skel_idle", getMemDC(), m[i]->mRc.left, m[i]->mRc.top);

		}
		else if (m[i]->state == 1)
		{
			IMAGEMANAGER->frameRender("skel_walk", getMemDC(), m[i]->mRc.left, m[i]->mRc.top);

		}
		else if (m[i]->state == 2)
		{
			IMAGEMANAGER->frameRender("skel_attack", getMemDC(), m[i]->mRc.left, m[i]->mRc.top);

		}
	}
	


	
	//RectangleMake(getMemDC(), foothold[0]);
//	RectangleMake(getMemDC(), foothold[1]);
	//RectangleMake(getMemDC(), foothold[2]);

	//RectangleMake(getMemDC(), m[0].mRc);
	//RectangleMake(getMemDC(), m[1].mRc);

	//RectangleMake(getMemDC(), cameraPoint1);

	IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), WINSIZE_X - 75, WINSIZE_Y / 2 - 40, _alpha);


	//sprintf(str, "���콺 ��ǥ x : %d , y : %d  m[0]�� ste : %d", _ptMouse.x, _ptMouse.y,m[0].ste);
	//TextOut(getMemDC(), 10, 10, str, strlen(str));
	
	
}


//========================================================================================================
//========================================================================================================
//========================================================================================================

/*
void popolScene::monsterMoveMent()
{
	
}

void popolScene::monsterInit()
{
	


	
	



}
*/