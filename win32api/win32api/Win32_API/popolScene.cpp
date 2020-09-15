#include "setDefine.h"
#include "popolScene.h"




HRESULT popolScene::init()
{
	IMAGEMANAGER->addImage("�޹��1", "Images/bakcground_day1.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��2", "Images/bakcground_day2.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��3", "Images/bakcground_day3.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���3", "Images/first_p.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���3_c", "Images/first_c.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("ü��", "Images/life.bmp", 27*2, 35*2, true, RGB(255, 0, 255));


	cameraPoint1 = RectMake(1250,0,100,WINSIZE_Y);

	lifeCount = 3;

	playerInit();
	monsterInit();
	
	return S_OK;
}

void popolScene::release()
{
}

void popolScene::update()
{

	playerMovement();
	monsterMoveMent();
	UI();
}

void popolScene::render()
{

	IMAGEMANAGER->render("�޹��1", getMemDC());
	IMAGEMANAGER->render("�޹��2", getMemDC());
	IMAGEMANAGER->render("�޹��3", getMemDC());



	IMAGEMANAGER->render("���3", getMemDC());
	

	for (int i = 0; i < lifeCount; i++)
	{
		IMAGEMANAGER->render("ü��", getMemDC(),30+i*55,50);
	}


	//RectangleMake(getMemDC(), rc);
	//RectangleMake(getMemDC(), rc2);
	//RectangleMake(getMemDC(), m[0].mRc);

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
	else if (state == 6)
	{
		IMAGEMANAGER->frameRender("p_hit", getMemDC(), rc.left, rc.top);
	}

	for (int i = 0; i < 2; i++)
	{
		if (m[i].state == 0)
		{
			IMAGEMANAGER->frameRender("skel_idle", getMemDC(), m[i].mRc.left, m[i].mRc.top);

		}
		else if (m[i].state == 1)
		{
			IMAGEMANAGER->frameRender("skel_walk", getMemDC(), m[i].mRc.left, m[i].mRc.top);

		}
		else if (m[i].state == 2)
		{
			IMAGEMANAGER->frameRender("skel_attack", getMemDC(), m[i].mRc.left, m[i].mRc.top);

		}
	}



	
	//RectangleMake(getMemDC(), foothold[0]);
//	RectangleMake(getMemDC(), foothold[1]);
	//RectangleMake(getMemDC(), foothold[2]);

	//RectangleMake(getMemDC(), m[0].mRc);

	RectangleMake(getMemDC(), cameraPoint1);

	sprintf(str, "���콺 ��ǥ x : %d , y : %d  m[0]�� ste : %d", _ptMouse.x, _ptMouse.y,m[0].ste);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
	
	
}

void popolScene::playerMovement()
{
	

	if (!attackOn && !rollOn)
	{
		if (!hitOn)
		{
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				rc.left += 5;
				rc.right += 5;
				cameraX += 5;
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
				cameraX -= 5;
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
		

		if (!jumpOn && floorOn)
		{
			if (!hitOn)
			{
				//����
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					state = 2;
					attackOn = true;
					player = IMAGEMANAGER->findImage("p_attack");
				}



				if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
				{
					state = 4;
					player = IMAGEMANAGER->findImage("p_roll");
					rollOn = true;
					noHitMode = true;
				}
			}
			

			//����
			if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
			{
				state = 3;
				player = IMAGEMANAGER->findImage("p_jump");

				jumpOn = true;

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
		player->setFrameX(attackState++ / 3);
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
	if (hitOn)
	{
		player = IMAGEMANAGER->findImage("p_hit");
		player->setFrameX(hitState++ / 10);
		player->setFrameY(dy);
		//hit����
		state = 6;

		//�÷��̾ ���� �����ʿ� ����
		if ((rc2.left + 30) - (m[hitMonNum].mRc.left + 30) > 0)
		{
			rc.left += 5;
			rc.right += 5;


		}
		else if ((rc2.left + 30) - (m[hitMonNum].mRc.left + 30) == 0)
		{
			//
		}
		//�÷��̾ ���� ���ʿ� ����
		else {
			rc.left -= 5;
			rc.right -= 5;

		}
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
		player = IMAGEMANAGER->findImage("p_idle");
		player->setFrameY(dy);
	}

	if (jumpGa >= 250)
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

	if (hitState > 10)
	{
		hitState = 0;
		hitOn = false;
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

	
	RECT tempRect;

	//������ ����ŭ �ݺ� 
	for (int i = 0; i < 1; i++)
	{
		//�������� ���ļ��� �浹�� �ȵ�! ->speed��ŭ ��ģ �κ��� ����
		if (IntersectRect(&tempRect, &rc2, &m[i].mRc) && !hitOn &&m[i].state ==2 && !noHitMode)
		{
			//���� ȸ������ �ƴ� �� ���Ϳ� �浹�Ѵٸ�
			if (!rollOn)
			{
				hitOn = true;
				noHitMode = true;
				hitMonNum = i;

				--lifeCount;

				if (lifeCount == 0)
				{
					//�� ��ȯ
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
		auto color = GetPixel(IMAGEMANAGER->findImage("���3_c")->getMemDC(), rc2.left + 30, i);

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
			player = IMAGEMANAGER->findImage("p_fall");
			player->setFrameY(dy);
			player->setFrameX(0);
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
			player = IMAGEMANAGER->findImage("p_idle");
			player->setFrameY(dy);
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

//========================================================================================================
//========================================================================================================
//========================================================================================================

void popolScene::monsterMoveMent()
{
	for (int i = 0; i < 2; i++)
	{
		
		if (!m[i].steMode && !m[i].attackOn)
		{
			//�÷��̾ ���� �����ʿ� ����
			if ((rc2.left + 30) - (m[i].mRc.left + 30) > 0)
			{
				m[i].mRc.left += 2;
				m[i].mRc.right += 2;
				m[i].dy = 0;

				m[i].state = 1;

				m[i].monsterImg = IMAGEMANAGER->findImage("skel_walk");
				m[i].monsterImg->setFrameY(m[i].dy);
				m[i].monsterImg->setFrameX(m[i].runState++ / 5);


				m[i].ste += 1;

			}
			else if ((rc2.left + 30) - (m[i].mRc.left + 30) == 0)
			{
				//
			}
			//�÷��̾ ���� ���ʿ� ����
			else {
				m[i].mRc.left -= 2;
				m[i].mRc.right -= 2;
				m[i].dy = 1;

				m[i].state = 1;

				m[i].monsterImg = IMAGEMANAGER->findImage("skel_walk");
				m[i].monsterImg->setFrameY(m[i].dy);
				m[i].monsterImg->setFrameX(m[i].runState++ / 5);

				m[i].ste += 1;
			}

		}



		

		//��� ���¶��
		if (m[i].state == 0)
		{
			m[i].monsterImg->setFrameY(m[i].dy);
			m[i].monsterImg->setFrameX(idleState++ / 5);
			if (m[i].ste > 0)
			{
				m[i].ste -= 1;
			}

			if (m[i].ste == 0)
			{
				m[i].steMode = false;
			}

		}

		if (m[i].attackOn)
		{

			m[i].monsterImg->setFrameY(m[i].dy);
			m[i].monsterImg->setFrameX(m[i].attackState++ / 5);
			m[i].ste += 1;
		}
		//hit, death �߰��ؾ���




		if (m[i].idleState > 90)
		{
			m[i].idleState = 0;
		}

		if (m[i].runState > 65)
		{
			m[i].runState = 0;
		}

		if (m[i].attackState > 90)
		{
			m[i].attackState = 0;
			m[i].attackOn = false;
			m[i].state = 0;
			m[i].monsterImg = IMAGEMANAGER->findImage("skel_idle");
			m[i].monsterImg->setFrameY(dy);
		}

		if (m[i].ste > 500 && !m[i].attackOn)
		{
			m[i].state = 0;
			m[i].monsterImg = IMAGEMANAGER->findImage("skel_idle");
			m[i].monsterImg->setFrameY(dy);
			m[i].steMode = true;
		}



		

		m[i].floorCheck = false;
		m[i].coll = false;

		//���� �ȼ� �浹

		//�ٴ� �浹
		for (int j = m[i].mRc.top; j < m[i].mRc.bottom; j++)
		{
			//�ȼ� �÷� �Ӽ��� ���� �浹 ������ ���� ����
			auto color = GetPixel(IMAGEMANAGER->findImage("���3_c")->getMemDC(), m[i].mRc.left + 30, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			//�ٴڿ� �浹�� ���
			if ((r == 0 && g == 0 && b == 0))
			{

				//�̵��ҷ��� ��ġ�� ������ ���� ũ�� �ʴٸ� 
				if (m[i].bHeight - j <= 20) {
					//��� �̹����� ���� ���� ������ ���󰡸鼭 ������ �� �ֵ���
					m[i].mRc.bottom = j + 5;
					m[i].mRc.top = m[i].mRc.bottom - 60;

					//�̹��� ���� ���� �κ��� ����
					m[i].coll = true;
					m[i].floorCheck = true;
					break;
				}

			}
			//���� �浹�� ���
			else if ((r == 255 && g == 0 && b == 0))
			{
				if (m[i].floorOn)
				{
					m[i].mRc.left = m[i].bFrameLeft;
					m[i].mRc.right = m[i].bFreameRight;
					m[i].coll = true;
					m[i].floorCheck = true;

				}
				else if (!m[i].floorOn)
				{
					m[i].mRc.left = m[i].bFrameLeft;
					m[i].mRc.right = m[i].bFreameRight;
					m[i].coll = true;

				}

			}


		}
		
		//�ٴ��� ���¿��� �浹���� �ʾ��� ��쿡 ���� �� �� 20 �ȼ��߿� ���� �ִٸ� �߶����� ����
		if (!m[i].coll && m[i].floorOn)
		{
			for (int j = m[i].mRc.bottom; j < m[i].mRc.bottom + 20; j++)
			{
				//�ȼ� �÷� �Ӽ��� ���� �浹 ������ ���� ����
				auto color = GetPixel(IMAGEMANAGER->findImage("���3_c")->getMemDC(), m[i].mRc.left + 30, j);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				//�̹��� ���� ���� �κ��� ����Ÿ ������ �ƴ� ���
				if (!(r == 255 & g == 0 & b == 255))
				{
					m[i].mRc.bottom = j + 5;
					m[i].mRc.top = m[i].mRc.bottom - 60;
					m[i].floorCheck = true;
					break;
				}
			}
		}
		
		RECT tempRect;

		for (int j = 0; j < 2; j++)
		{
			//�������� ���ļ��� �浹�� �ȵ�! ->speed��ŭ ��ģ �κ��� ����
			if (IntersectRect(&tempRect, &rc2, &m[i].mRc) && !m[i].steMode)
			{
				m[i].state = 2;
				m[i].attackOn = true;
				m[i].monsterImg = IMAGEMANAGER->findImage("skel_attack");
			}

		}
		

		if (m[i].floorCheck)
		{
			m[i].floorOn = true;
		}
		else if (!m[i].floorCheck)
		{
			m[i].floorOn = false;

		}


		//�ٴ��� �ƴϰ� ���� ���� �ƴ϶�� 
		if (!m[i].floorOn)
		{
			m[i].mRc.top += 5;
			m[i].mRc.bottom += 5;
			m[i].landing = 1;

		}

		if (m[i].landing == 1 && m[i].floorOn)
		{

			m[i].landing = 0;

		}


		if (m[i].coll)
		{
		}





		m[i].bFrameLeft = m[i].mRc.left;
		m[i].bFreameRight = m[i].mRc.right;
		m[i].bHeight = m[i].mRc.bottom;
		

	}
	



	
}

void popolScene::playerInit()
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


	player = IMAGEMANAGER->findImage("p_idle");

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	//�÷��̾� �̹���
	rc = RectMakeCenter(_x, _y, 60, 60);
	//�÷��̾� �浹ü
	rc2 = RectMake(rc.left + 30, rc.top, 60, 60);

	_probeY = rc2.top + player->getHeight() / 2;
	bHeight = rc2.bottom;
}

void popolScene::monsterInit()
{
	IMAGEMANAGER->addFrameImage("skel_idle", "Images/skel/idle.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1144, 128, 11, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_attack", "Images/skel/attack.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1872, 148, 18, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_death", "Images/skel/death.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1560, 128, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_walk", "Images/skel/walk.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 1352, 132, 13, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_hit", "Images/skel/hit.bmp",
		WINSIZE_X / 2, WINSIZE_Y / 2, 832, 128, 8, 2, true, RGB(255, 0, 255));


	
	for (int i = 0; i < 2; i++)
	{
		


		m[i].monsterImg = IMAGEMANAGER->findImage("skel_idle");
		m[i].monsterImg->setFrameX(0);
		m[i].monsterImg->setFrameY(0);
		m[i].state = 0;
		m[i].dy = 0;

	}
	
	m[0].mRc = RectMake(800, 500, 60, 60);
	m[1].mRc = RectMake(1000, 450, 60, 60);


	
	



}

void popolScene::cameraMove()
{

	RECT tempRect2;
	if (IntersectRect(&tempRect2, &rc2, &cameraPoint1))
	{
		if (cameraState == 0)
		{

		}
		else
		{

		}
	}
	


}

void popolScene::UI()
{



}
