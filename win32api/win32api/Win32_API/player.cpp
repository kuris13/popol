#include "setDefine.h"
#include "player.h"


void player::playerMovement()
{

	if (!attackOn && !rollOn)
	{
		if (!hitOn)
		{
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				rc.left += 5;
				rc.right += 5;
		
				dy = 0;
				if (!jumpOn)
				{
					state = 1;

					playerImg = IMAGEMANAGER->findImage("p_run");
					playerImg->setFrameY(dy);
					playerImg->setFrameX(runState++ / 5);
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

					playerImg = IMAGEMANAGER->findImage("p_run");
					playerImg->setFrameY(dy);
					playerImg->setFrameX(runState++ / 5);
				}
			}
		}


		if (!jumpOn && floorOn)
		{
			if (!hitOn)
			{
				//공격
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					state = 2;
					attackOn = true;
					playerImg = IMAGEMANAGER->findImage("p_attack");
				}



				if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
				{
					state = 4;
					playerImg = IMAGEMANAGER->findImage("p_roll");
					rollOn = true;
					noHitMode = true;
				}
			}


			//점프
			if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
			{
				state = 3;
				playerImg = IMAGEMANAGER->findImage("p_jump");

				jumpOn = true;

			}
		}




	}


	//대기 상태라면
	if (state == 0)
	{
		playerImg->setFrameY(dy);
		playerImg->setFrameX(idleState++ / 5);
	}

	if (attackOn)
	{
		playerImg->setFrameY(dy);
		playerImg->setFrameX(attackState++ / 3);
	}
	else if (jumpOn)
	{
		playerImg->setFrameY(dy);

		if (jumpState < 25)
		{
			playerImg->setFrameX(jumpState++ / 5);
		}


		rc.top -= jumpSpeed;
		rc.bottom -= jumpSpeed;

		jumpGa += jumpSpeed;

	}
	else if (rollOn)
	{
		playerImg->setFrameY(dy);
		playerImg->setFrameX(rollState++ / 5);
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
	if (hitOn)
	{
		playerImg = IMAGEMANAGER->findImage("p_hit");
		playerImg->setFrameX(hitState++ / 10);
		playerImg->setFrameY(dy);
		//hit상태
		state = 6;

		/*
		//플레이어가 몬스터 오른쪽에 있음
		if ((rc2.left + 30) - (m[hitMonNum].mRc.left + 30) > 0)
		{
			rc.left += 5;
			rc.right += 5;


		}
		else if ((rc2.left + 30) - (m[hitMonNum].mRc.left + 30) == 0)
		{
			//
		}
		//플레이어가 몬스터 왼쪽에 있음
		else {
			rc.left -= 5;
			rc.right -= 5;

		}
		*/
	}
	
	if (noHitMode)
	{
		noHitGa++;

		if (noHitGa >= 50)
		{
			noHitMode = false;
			noHitGa = 0;
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

	if (attackState > 66)
	{
		attackState = 0;
		attackOn = false;
		state = 0;
		playerImg = IMAGEMANAGER->findImage("p_idle");
		playerImg->setFrameY(dy);
	}

	if (jumpGa >= 250)
	{
		jumpState = 0;
		jumpGa = 0;
		jumpOn = false;
		state = 0;
		playerImg = IMAGEMANAGER->findImage("p_idle");
		playerImg->setFrameY(dy);

	}
	if (rollState > 40)
	{
		rollState = 0;
		rollOn = false;
		state = 0;
		playerImg = IMAGEMANAGER->findImage("p_idle");
		playerImg->setFrameY(dy);
	}

	if (hitState > 10)
	{
		hitState = 0;
		hitOn = false;
		state = 0;
		playerImg = IMAGEMANAGER->findImage("p_idle");
		playerImg->setFrameY(dy);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (!jumpOn && !attackOn && !rollOn)
		{
			state = 0;

			playerImg = IMAGEMANAGER->findImage("p_idle");
			playerImg->setFrameY(dy);
		}


	}

	/*
	RECT tempRect;

	//몬스터의 수많큼 반복 
	for (int i = 0; i < 1; i++)
	{
		//테투리만 겹쳐서는 충돌이 안됨! ->speed만큼 겹친 부분이 존재
		if (IntersectRect(&tempRect, &rc2, &m[i].mRc) && !hitOn &&m[i].state == 2 && !noHitMode)
		{
			//내가 회피중이 아닐 때 몬스터와 충돌한다면
			if (!rollOn)
			{
				hitOn = true;
				noHitMode = true;
				hitMonNum = i;

				--lifeCount;

				if (lifeCount == 0)
				{
					//씬 전환
				}

			}

		}

	}

	*/

	floorCheck = false;
	coll = false;

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

	_probeY = rc2.top + 30;

	//바닥 충돌
	for (int i = _probeY - 30; i < _probeY + 30; i++)
	{
		//픽셀 컬러 속성에 따른 충돌 판정을 위해 만듦
		auto color = GetPixel(IMAGEMANAGER->findImage(backName)->getMemDC(), rc2.left + 30, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//바닥에 충돌한 경우
		if ((r == 0 && g == 0 && b == 0))
		{

			//이동할려는 위치가 나보다 많이 크지 않다면 
			if (bHeight - i <= 20) {
				//대상 이미지의 가장 겉의 라인을 따라가면서 움직일 수 있도록
				rc.bottom = i + 5;
				rc.top = rc.bottom - 60;

				//이미지 끼리 닿인 부분의 색은
				coll = true;
				floorCheck = true;
				break;
			}

		}
		//벽에 충돌한 경우
		else if ((r == 255 && g == 0 && b == 0))
		{
			if (floorOn)
			{
				rc.left = bFrameLeft;
				rc.right = bFreameRight;
				coll = true;
				floorCheck = true;

			}
			else if (!floorOn)
			{
				rc.left = bFrameLeft;
				rc.right = bFreameRight;
				coll = true;

			}

		}


	}

	//바닥인 상태에서 충돌하지 않았을 경우에 만약 내 밑 20 픽셀중에 땅이 있다면 추락하지 않음
	if (!coll && floorOn && !jumpOn)
	{
		for (int i = _probeY + 30; i < _probeY + 30 + 20; i++)
		{
			//픽셀 컬러 속성에 따른 충돌 판정을 위해 만듦
			auto color = GetPixel(IMAGEMANAGER->findImage("배경3_c")->getMemDC(), rc2.left + 30, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			//이미지 끼리 닿인 부분이 마젠타 색상이 아닐 경우
			if (!(r == 255 & g == 0 & b == 255))
			{
				rc.bottom = i + 5;
				rc.top = rc.bottom - 60;
				floorCheck = true;
				break;
			}
		}
	}





	if (floorCheck)
	{
		floorOn = true;
	}
	else if (!floorCheck)
	{
		floorOn = false;

	}


	//바닥이 아니고 점프 중이 아니라면 
	if (!floorOn && !jumpOn)
	{
		if (!rollOn)
		{
			playerImg = IMAGEMANAGER->findImage("p_fall");
			playerImg->setFrameY(dy);
			playerImg->setFrameX(0);
			state = 5;
		}

		rc.top += 5;
		rc.bottom += 5;
		landing = 1;

	}

	if (landing == 1 && floorOn)
	{
		if (!rollOn)
		{
			playerImg = IMAGEMANAGER->findImage("p_idle");
			playerImg->setFrameY(dy);
			state = 0;
		}



		landing = 0;

	}

	if (hitOn)
	{


	}

	if (coll)
	{
	}





	bFrameLeft = rc.left;
	bFreameRight = rc.right;
	bHeight = rc.bottom;

}

void player::playerInit()
{

	IMAGEMANAGER->addFrameImage("p_idle", "Images/player/idle.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1800, 120, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_run", "Images/player/run.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 960, 120, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_attack", "Images/player/attack.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 2640, 130, 22, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_roll", "Images/player/roll.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1800, 120, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_jump", "Images/player/jump.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 600, 124, 5, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_fall", "Images/player/fall.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 240, 124, 2, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_hit", "Images/player/landing.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 240, 124, 2, 2, true, RGB(255, 0, 255));


	playerImg = IMAGEMANAGER->findImage("p_idle");

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	//플레이어 이미지
	rc = RectMakeCenter(_x, _y, 60, 60);
	//플레이어 충돌체
	rc2 = RectMake(rc.left + 30, rc.top, 60, 60);

	_probeY = rc2.top + playerImg->getHeight() / 2;
	bHeight = rc2.bottom;

}

