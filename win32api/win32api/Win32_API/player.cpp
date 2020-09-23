#include "setDefine.h"
#include "player.h"


void player::playerMovement()
{

	if (lifeCount == 0)
	{
		deathOn = true;
		playerImg = IMAGEMANAGER->findImage("p_death");
		playerImg->setFrameY(dy);
		playerImg->setFrameX(deathState++ / 5);

		if (deathState > 75)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				lifeCount += 5;
			}

			
		}

	}
	else {

		if (!attackOn && !rollOn)
		{
			if (!hitOn)
			{
				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					rc.left += 5;
					rc.right += 5;
					//CAMERA += 5;
					dy = 0;
					if (!jumpOn)
					{
						state = 1;

						playerImg = IMAGEMANAGER->findImage("p_run");
						playerImg->setFrameY(dy);
						playerImg->setFrameX(runState++);
					}

				}

				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					rc.left -= 5;
					rc.right -= 5;
					//CAMERA -= 5;
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
					//����
					if (KEYMANAGER->isOnceKeyDown(0x5A))
					{
						state = 2;
						attackOn = true;
						playerImg = IMAGEMANAGER->findImage("p_attack");
					}



					if (KEYMANAGER->isOnceKeyDown(0x43))
					{
						state = 4;
						playerImg = IMAGEMANAGER->findImage("p_roll");
						rollOn = true;
						noHitMode = true;
					}
				}


				//����
				if (KEYMANAGER->isOnceKeyDown(0x58))
				{
					state = 3;
					playerImg = IMAGEMANAGER->findImage("p_jump");

					jumpOn = true;

				}
			}




		}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			useItem();
		}

		//��� ���¶��
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
			playerImg->setFrameX(rollState++);
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
			//hit����
			state = 6;


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

		if (runState > 8)
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

		if (jumpGa >= 200)
		{
			jumpState = 0;
			jumpGa = 0;
			jumpOn = false;
			state = 0;
			playerImg = IMAGEMANAGER->findImage("p_idle");
			playerImg->setFrameY(dy);

		}
		if (rollState > 8)
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


		RECT tempRect;

		//������ ����ŭ �ݺ� 
		for (int i = 0; i < monstCount; i++)
		{

			//�������� ���ļ��� �浹�� �ȵ�! ->speed��ŭ ��ģ �κ��� ����
			if (IntersectRect(&tempRect, &rc2, &mRc[i]) && !hitOn &&isMonsterAttack[i] && !attackOn && !noHitMode)
			{
				//���� ȸ������ �ƴ� �� ���Ϳ� �浹�Ѵٸ�
				if (!rollOn && ((IMAGEMANAGER->findImage("skel_attack")->getFrameX() > 7) && (IMAGEMANAGER->findImage("skel_attack")->getFrameX() < 12)))
				{
					hitOn = true;
					noHitMode = true;
					hitMonNum = i;

					--lifeCount;

					//���� ���ͺ��� �����ʿ� �ִٸ� 
					if (rc2.left + 30 > mRc[i].left + 30)
					{
						rc.left += 20;
						rc.right += 20;

					}
					else
					{
						rc.left -= 20;
						rc.right -= 20;
					}
				}

			}

		}



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

		//�ٴ� �浹
		for (int i = _probeY - 30; i < _probeY + 30; i++)
		{
			//�ȼ� �÷� �Ӽ��� ���� �浹 ������ ���� ����
			auto color = GetPixel(IMAGEMANAGER->findImage(backName)->getMemDC(), rc2.left + 30, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			//�ٴڿ� �浹�� ���
			if ((r == 0 && g == 0 && b == 0))
			{

				//�̵��ҷ��� ��ġ�� ������ ���� ũ�� �ʴٸ� 
				if (bHeight - i <= 20) {
					//��� �̹����� ���� ���� ������ ���󰡸鼭 ������ �� �ֵ���
					rc.bottom = i + 5;
					rc.top = rc.bottom - 60;

					//�̹��� ���� ���� �κ��� ����
					coll = true;
					floorCheck = true;
					break;
				}

			}
			//���� �浹�� ���
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

		//�ٴ��� ���¿��� �浹���� �ʾ��� ��쿡 ���� �� �� 20 �ȼ��߿� ���� �ִٸ� �߶����� ����
		if (!coll && floorOn && !jumpOn)
		{
			for (int i = _probeY + 30; i < _probeY + 30 + 20; i++)
			{
				//�ȼ� �÷� �Ӽ��� ���� �浹 ������ ���� ����
				auto color = GetPixel(IMAGEMANAGER->findImage("���3_c")->getMemDC(), rc2.left + 30, i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				//�̹��� ���� ���� �κ��� ����Ÿ ������ �ƴ� ���
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


		//�ٴ��� �ƴϰ� ���� ���� �ƴ϶�� 
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


	//	CAMERA = rc.left - bFrameLeft;
		bFrameLeft = rc.left;
		bFreameRight = rc.right;
		bHeight = rc.bottom;


	}

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

	IMAGEMANAGER->addFrameImage("p_death", "Images/player/death.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1800, 120, 15, 2, true, RGB(255, 0, 255));


	playerImg = IMAGEMANAGER->findImage("p_idle");

	_x =0;
	_y =0;

	//�÷��̾� �̹���
	rc = RectMakeCenter(_x, _y, 60, 60);
	//�÷��̾� �浹ü
	rc2 = RectMake(rc.left + 30, rc.top, 60, 60);

	_probeY = rc2.top + playerImg->getHeight() / 2;
	bHeight = rc2.bottom;

	lifeCount = 4;
	bFrameLeft = rc.left;

	

}

void player::useItem()
{

	invenVec2.erase(invenVec2.begin());





}


