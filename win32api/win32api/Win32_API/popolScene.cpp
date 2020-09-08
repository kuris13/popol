#include "setDefine.h"
#include "popolScene.h"




HRESULT popolScene::init()
{
	IMAGEMANAGER->addImage("배경3", "Images/배경3.bmp", WINSIZE_X , WINSIZE_Y);

	IMAGEMANAGER->addFrameImage("p_idle", "Images/player/idle.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1800, 120, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_run", "Images/player/run.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 960, 120, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_attack", "Images/player/attack.bmp",
		WINSIZE_X /2 , WINSIZE_Y/2, 2640, 130,22,2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_roll", "Images/player/roll.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1800, 120, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_jump", "Images/player/jump.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 600, 124, 5, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_fall", "Images/player/fall.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 240, 124, 2, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_landing", "Images/player/landing.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 240, 124, 2, 2, true, RGB(255, 0, 255));




	player = IMAGEMANAGER->findImage("p_idle");

	//플레이어 이미지
	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 60, 60);
	//플레이어 충돌체
	rc2 = RectMake(rc.left + 30, rc.top, 60, 60);

	

	foothold[0] = RectMake(0,444,210,200);
	foothold[1] = RectMake(210, 448, 145, 15);
	foothold[2] = RectMake(0, 642, WINSIZE_X, 200);


	
	return S_OK;
}

void popolScene::release()
{
}

void popolScene::update()
{


	



	if (!attackOn && !rollOn)
	{
		if (!jumpOn && floorOn)
		{
			//공격
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				state = 2;
				attackOn = true;
				player = IMAGEMANAGER->findImage("p_attack");
			}

			//점프
			if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
			{
				state = 3;
				player = IMAGEMANAGER->findImage("p_jump");
				landing = 1;
				jumpOn = true;

			}

			if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
			{
				state = 4;
				player = IMAGEMANAGER->findImage("p_roll");
				jumpOn = true;
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			rc.left += 5;
			rc.right += 5;

			dy = 0;
			if (!jumpOn)
			{
				state = 1;
			
				player = IMAGEMANAGER->findImage("p_run");
				player->setFrameY(dy);
				player->setFrameX(runState++ / 5);
			}
			
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			rc.left -= 5;
			rc.right -= 5;

			dy = 1;
			if (!jumpOn)
			{
				state = 1;
		
				player = IMAGEMANAGER->findImage("p_run");
				player->setFrameY(dy);
				player->setFrameX(runState++ / 5);
			}
		}
		

	}
	

	//대기 상태라면
	if (state == 0)
	{
		player->setFrameY(dy);
		player->setFrameX(idleState++ / 5);
	}

	if (attackOn)
	{
		player->setFrameY(dy);
		player->setFrameX(attackState++ / 5);
	}
	else if (jumpOn)
	{
		player->setFrameY(dy);

		if (jumpState < 25)
		{
			player->setFrameX(jumpState++ / 5);
		}
		

		rc.top -= jumpSpeed;
		rc.bottom -= jumpSpeed;

		jumpGa += jumpSpeed;

	}
	else if (rollOn)
	{
		player->setFrameY(dy);
		player->setFrameX(rollState++ / 5);
	}
	
	
	

	if (idleState > 90)
	{
		idleState = 0;
	}

	if (runState > 40)
	{
		runState = 0;
	}

	if (attackState > 110)
	{
		attackState = 0;
		attackOn = false;
		state = 0;
		player = IMAGEMANAGER->findImage("p_idle");
		player->setFrameY(dy);
	}
	

	if (jumpGa >= 200)
	{
		jumpState = 0;
		jumpGa = 0;
		jumpOn = false;
		state = 0;
		player = IMAGEMANAGER->findImage("p_idle");
		player->setFrameY(dy);

	}
	if (rollState > 40)
	{
		rollState = 0;
		rollOn = false;
		state = 0;
		player = IMAGEMANAGER->findImage("p_idle");
		player->setFrameY(dy);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (!jumpOn)
		{
			state = 0;

			player = IMAGEMANAGER->findImage("p_idle");
			player->setFrameY(dy);
		}
		

	}


	//바닥이 아니고 점프 중이 아니라면 
	if (!floorOn && !jumpOn)
	{
		player = IMAGEMANAGER->findImage("p_fall");
		player->setFrameY(dy);
		player->setFrameX(0);
		state = 5;
		rc.top += 5;
		rc.bottom += 5;

	}
	
	if (landing ==1 && !jumpOn)
	{
		player = IMAGEMANAGER->findImage("p_idle");
		player->setFrameY(dy);
		state = 0;
		landing = 0;
	}

	RECT tempRect;

	for (int i = 0; i < 3; i++)
	{
		if (IntersectRect(&tempRect, &rc, &foothold[i]))
		{
			floorOn = true;
			landing = 0;
			break;
		}
		else
		{
			floorOn = false;
		}
	}
	


	
	rc2 = RectMake(rc.left + 30, rc.top, 60, 60);
	cout << "플레이어의 좌표 : " << rc.left <<" , "<< rc.top<<endl;

	

}

void popolScene::render()
{
	IMAGEMANAGER->render("배경3", getMemDC());
	//RectangleMake(getMemDC(), rc2);

	

	if (state == 0)
	{
		IMAGEMANAGER->frameRender("p_idle", getMemDC(), rc.left, rc.top);
	}
	else if (state == 1)
	{
		IMAGEMANAGER->frameRender("p_run", getMemDC(), rc.left, rc.top);
	}
	else if (state == 2)
	{
		IMAGEMANAGER->frameRender("p_attack", getMemDC(), rc.left, rc.top);
	}
	else if (state == 3)
	{
		IMAGEMANAGER->frameRender("p_jump", getMemDC(), rc.left, rc.top);
	}
	else if (state == 4)
	{
		IMAGEMANAGER->frameRender("p_roll", getMemDC(), rc.left, rc.top);
	}
	else if (state == 5)
	{
		IMAGEMANAGER->frameRender("p_fall", getMemDC(), rc.left, rc.top);
	}

	RectangleMake(getMemDC(), foothold[0]);
	RectangleMake(getMemDC(), foothold[1]);
	RectangleMake(getMemDC(), foothold[2]);

	sprintf(str, "마우스 좌표 x : %d , y : %d       fall :  %d    jump : %d   state : %d", _ptMouse.x, _ptMouse.y,floorOn,jumpOn, state);
	TextOut(getMemDC(), 10, 10, str, strlen(str));

}
