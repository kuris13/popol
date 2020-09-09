#include "setDefine.h"
#include "popolScene.h"




HRESULT popolScene::init()
{
	IMAGEMANAGER->addImage("���3", "Images/first.bmp", WINSIZE_X , WINSIZE_Y);

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

	//�÷��̾� �̹���
	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 60, 60);
	//�÷��̾� �浹ü
	rc2 = RectMake(rc.left + 30, rc.top, 60, 60);

	foothold[0] = RectMake(0, 640, WINSIZE_X, 200);
	foothold[1] = RectMake(0, 580, 180, 140);

	
	return S_OK;
}

void popolScene::release()
{
}

void popolScene::update()
{


	



	if (!attackOn && !rollOn)
	{

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

		if (!jumpOn && floorOn)
		{
			//����
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				state = 2;
				attackOn = true;
				player = IMAGEMANAGER->findImage("p_attack");
			}

			//����
			if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
			{
				state = 3;
				player = IMAGEMANAGER->findImage("p_jump");
				
				jumpOn = true;

			}

			if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
			{
				state = 4;
				player = IMAGEMANAGER->findImage("p_roll");
				rollOn = true;
			}
		}

		
		

	}
	

	//��� ���¶��
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
		if (dy == 0)
		{
			rc.left += 5;
			rc.right += 5;
		}
		else if (dy == 1)
		{
			rc.left -= 5;
			rc.right -= 5;
		}
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
		if (!jumpOn && !attackOn && !rollOn)
		{
			state = 0;

			player = IMAGEMANAGER->findImage("p_idle");
			player->setFrameY(dy);
		}
		

	}

	if (attackOn)
	{
		if (dy == 0)
		{
			rc2 = RectMake(rc.left + 30, rc.top, 90, 60);
		}
		else if (dy == 1)
		{
			rc2 = RectMake(rc.left, rc.top, 90, 60);
		}

	}
	else
	{
		rc2 = RectMake(rc.left + 30, rc.top, 60, 60);
	}
	

	RECT tempRect;

	for (int i = 0; i < 2; i++)
	{
		//�������� ���ļ��� �浹�� �ȵ�! ->speed��ŭ ��ģ �κ��� ����
		if (IntersectRect(&tempRect, &rc2, &foothold[i]))
		{
			cout << i << "���� �浹" << endl;
			cout <<"   ���� rect ��->         left : "<<rc.left<<" , right : "<<rc.right <<", top : "<<rc.top<<", bottom : "<<rc.bottom << endl
				 <<",  �浹�� ��ü�� ��ǥ��-> left : "<< foothold[i].left<<", right : "<<foothold[i].right <<", top : "<<foothold[i].top 
				 <<", bottom : "<<foothold[i].bottom <<endl;

			if (rc2.left <= foothold[i].right && rc2.right >= foothold[i].right && rc2.bottom-6 >= foothold[i].top)
			{
				
				//�������� �̵��Ѵٸ� �� �������� ��ġ�� �̵� (�̵� x)
				if (rc.left < bFrameLeft)
				{
					rc.left = bFrameLeft;
					rc.right = bFreameRight;
				}
				
				//rc2.left = foothold[i].right;
				//rc2.right = rc2.left + 60;
				cout << "�������� �浹" << endl;
			}

			//rc2�� �ٴ��� �浹 ���� ��� 
			if (rc2.bottom == foothold[i].top+5 && rc.top < foothold[i].top)
			{
				rc.bottom = foothold[i].top+5;
				rc.top = rc.bottom - 60;
				floorOn = true;
				cout << "���� �浹" << endl;
				
				//break;
				
				
			}
		}
		else
		{
			floorOn = false;
			
		}
	}
	
	//�ٴ��� �ƴϰ� ���� ���� �ƴ϶�� 
	if (!floorOn && !jumpOn)
	{
		player = IMAGEMANAGER->findImage("p_fall");
		player->setFrameY(dy);
		player->setFrameX(0);
		state = 5;
		rc.top += 5;
		rc.bottom += 5;
		landing = 1;

	}

	

	if (landing == 1 && floorOn)
	{
		player = IMAGEMANAGER->findImage("p_idle");
		player->setFrameY(dy);
		state = 0;
		landing = 0;

	}


	
	cout << "�÷��̾��� ��ǥ : " << rc.left <<" , "<< rc.top<<endl;

	bFrameLeft = rc.left;
	bFreameRight = rc.right;

}

void popolScene::render()
{
	IMAGEMANAGER->render("���3", getMemDC());
	

	RectangleMake(getMemDC(), rc);
	RectangleMake(getMemDC(), rc2);

	if (attackOn)
	{
		auto brush = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(getMemDC(), &rc2, brush);
		DeleteObject(brush);
	}
	else if (rollOn)
	{
		auto brush = CreateSolidBrush(RGB(0, 255, 0));
		FillRect(getMemDC(), &rc2, brush);
		DeleteObject(brush);
	}
	

	

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

	sprintf(str, "���콺 ��ǥ x : %d , y : %d       fall :  %d    jump : %d   state : %d   landing : %d", _ptMouse.x, _ptMouse.y,floorOn,jumpOn, state, landing);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
	
	
}
