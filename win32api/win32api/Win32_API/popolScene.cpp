#include "setDefine.h"
#include "popolScene.h"




HRESULT popolScene::init()
{
	IMAGEMANAGER->addImage("뒷배경1", "Images/bakcground_day1.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒷배경2", "Images/bakcground_day2.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒷배경3", "Images/bakcground_day3.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("배경3", "Images/first_p.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경3_c", "Images/first_c.bmp", 1312, 768, true, RGB(255, 0, 255));


	

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

}

void popolScene::render()
{

	IMAGEMANAGER->render("뒷배경1", getMemDC());
	IMAGEMANAGER->render("뒷배경2", getMemDC());
	IMAGEMANAGER->render("뒷배경3", getMemDC());



	IMAGEMANAGER->render("배경3", getMemDC());
	




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


	if (m[0].state == 0)
	{
		IMAGEMANAGER->frameRender("skel_idle", getMemDC(), m[0].mRc.left, m[0].mRc.top);

	}else if (m[0].state == 1)
	{
		IMAGEMANAGER->frameRender("skel_walk", getMemDC(), m[0].mRc.left, m[0].mRc.top);

	}else if (m[0].state == 2)
	{
		IMAGEMANAGER->frameRender("skel_attack", getMemDC(), m[0].mRc.left, m[0].mRc.top);

	}


	
	//RectangleMake(getMemDC(), foothold[0]);
//	RectangleMake(getMemDC(), foothold[1]);
	//RectangleMake(getMemDC(), foothold[2]);

	//RectangleMake(getMemDC(), m[0].mRc);

	sprintf(str, "마우스 좌표 x : %d , y : %d  m[0]의 ste : %d", _ptMouse.x, _ptMouse.y,m[0].ste);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
	
	
}

void popolScene::playerMovement()
{
	cout << "업데이트 시작 좌표 y :" << rc2.bottom << endl;

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
				//공격
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
			

			//점프
			if (KEYMANAGER->isOnceKeyDown(VK_SHIFT))
			{
				state = 3;
				player = IMAGEMANAGER->findImage("p_jump");

				jumpOn = true;

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
		//hit상태
		state = 6;

		//플레이어가 몬스터 오른쪽에 있음
		if ((rc2.left + 30) - (m[0].mRc.left + 30) > 0)
		{
			rc.left += 5;
			rc.right += 5;


		}
		else if ((rc2.left + 30) - (m[0].mRc.left + 30) == 0)
		{
			//
		}
		//플레이어가 몬스터 왼쪽에 있음
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

	if (attackState > 110)
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

	//몬스터의 수많큼 반복 
	for (int i = 0; i < 1; i++)
	{
		//테투리만 겹쳐서는 충돌이 안됨! ->speed만큼 겹친 부분이 존재
		if (IntersectRect(&tempRect, &rc2, &m[i].mRc) && !hitOn &&m[i].state ==2 && !noHitMode)
		{
			//내가 회피중이 아닐 때 몬스터와 충돌한다면
			if (!rollOn)
			{
				hitOn = true;
				noHitMode = true;
				cout << "현재 몬스터와 충돌 중 " << endl;
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
	//픽셀 충돌
	//cout << "충돌 직전 value 측정 " << endl;
	//cout << "==============================================" << endl;
	//cout << "rc의 bottom값 : " << rc.bottom << " rc2의 bottom값 : " << rc2.bottom << endl;
	//cout << "_probeY (이미지 중간 값)의 값 : " << _probeY << endl;
	//cout << "==============================================" << endl;

	//바닥 충돌
	for (int i = _probeY - 30; i < _probeY + 30; i++)
	{
		//픽셀 컬러 속성에 따른 충돌 판정을 위해 만듦
		auto color = GetPixel(IMAGEMANAGER->findImage("배경3_c")->getMemDC(), rc2.left + 30, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//바닥에 충돌한 경우
		if ((r == 0 && g == 0 && b == 0))
		{

			//이동할려는 위치가 나보다 많이 크지 않다면 
			if (bHeight - i <= 20) {
				cout << "충돌함, 충돌한 좌표 ->x : " << rc2.left + 30 << ", y : " << i << endl;
				cout << i << " - " << bHeight << " = " << i - bHeight << endl;
				//대상 이미지의 가장 겉의 라인을 따라가면서 움직일 수 있도록
				rc.bottom = i + 5;
				rc.top = rc.bottom - 60;

				//이미지 끼리 닿인 부분의 색은
				//cout << "검사할 부분의 좌표는 -> x : " << rc2.left + 15 << "y : " << i << endl;
				cout << "r : " << r << "g : " << g << "b : " << b << "입니다." << endl;
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
				//cout << "벽에 충돌함 ===============================" << endl;
				rc.left = bFrameLeft;
				rc.right = bFreameRight;
				coll = true;
				floorCheck = true;

			}
			else if (!floorOn)
			{
				//cout << "벽에 충돌함 ===============================" << endl;
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
				cout << "밑에 땅이 가까이 있기 때문에 추락하지 않음 " << endl;
				floorCheck = true;
				break;
			}
		}
	}

	
	
	

	if (floorCheck)
	{
		floorOn = true;
		cout << "바닥임" << endl;
	}
	else if (!floorCheck)
	{
		floorOn = false;
		cout << "충돌 안 함, 내 좌표 ->x : " << rc2.left << ", y : " << rc2.bottom << endl;
		cout << "바닥이 아님" << endl;
	}


	//바닥이 아니고 점프 중이 아니라면 
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
		cout << "추락함" << endl;

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
		cout << "몬스터에게 공격 당함" << endl;
		cout << hitState << endl;

	}
	
	//cout << "이번 플레이어 rc의 좌표 : " << rc.left << " , " << rc.bottom << endl;
	//cout << "이번 플레이어 rc2의 좌표 : " << rc2.left << " , " << rc2.bottom << endl;
	if (coll)
	{
		cout << "이번 업데이트에서는 충돌함 " << endl;
	}


	cout << endl;



	bFrameLeft = rc.left;
	bFreameRight = rc.right;
	bHeight = rc.bottom;
}

//========================================================================================================
//========================================================================================================
//========================================================================================================

void popolScene::monsterMoveMent()
{
	cout << endl;
	cout << "몬스터 업데이트 시작 좌표 y :" << rc2.bottom << endl;

	if (!m[0].steMode && !m[0].attackOn)
	{
		//플레이어가 몬스터 오른쪽에 있음
		if ((rc2.left + 30) - (m[0].mRc.left + 30) > 0)
		{
			m[0].mRc.left += 2;
			m[0].mRc.right += 2;
			m[0].dy = 0;

			m[0].state = 1;

			m[0].monsterImg = IMAGEMANAGER->findImage("skel_walk");
			m[0].monsterImg->setFrameY(m[0].dy);
			m[0].monsterImg->setFrameX(m[0].runState++ / 5);


			m[0].ste += 1;

		}
		else if ((rc2.left + 30) - (m[0].mRc.left + 30) == 0)
		{
			//
		}
		//플레이어가 몬스터 왼쪽에 있음
		else {
			m[0].mRc.left -= 2;
			m[0].mRc.right -= 2;
			m[0].dy = 1;

			m[0].state = 1;

			m[0].monsterImg = IMAGEMANAGER->findImage("skel_walk");
			m[0].monsterImg->setFrameY(m[0].dy);
			m[0].monsterImg->setFrameX(m[0].runState++ / 5);

			m[0].ste += 1;
		}

	}





	//대기 상태라면
	if (m[0].state == 0)
	{
		m[0].monsterImg->setFrameY(m[0].dy);
		m[0].monsterImg->setFrameX(idleState++ / 5);
		if (m[0].ste > 0)
		{
			m[0].ste -= 1;
		}

		if (m[0].ste == 0)
		{
			m[0].steMode = false;
		}

	}

	if (m[0].attackOn)
	{

		m[0].monsterImg->setFrameY(m[0].dy);
		m[0].monsterImg->setFrameX(m[0].attackState++ / 5);
		m[0].ste += 1;
	}
	//hit, death 추가해야함
	



	if (m[0].idleState > 90)
	{
		m[0].idleState = 0;
	}

	if (m[0].runState > 65)
	{
		m[0].runState = 0;
	}

	if (m[0].attackState > 90)
	{
		m[0].attackState = 0;
		m[0].attackOn = false;
		m[0].state = 0;
		m[0].monsterImg = IMAGEMANAGER->findImage("skel_idle");
		m[0].monsterImg->setFrameY(dy);
	}

	if (m[0].ste > 500 && !m[0].attackOn)
	{
		m[0].state = 0;
		m[0].monsterImg = IMAGEMANAGER->findImage("skel_idle");
		m[0].monsterImg->setFrameY(dy);
		m[0].steMode = true;
	}





	m[0].floorCheck = false;
	m[0].coll = false;

	//몬스터 픽셀 충돌
	cout << "충돌 직전 value 측정 " << endl;
	cout << "==============================================" << endl;
	cout << "monster의 bottom값 : " << m[0].mRc.bottom << endl;
	cout << "==============================================" << endl;

	//바닥 충돌
	for (int i = m[0].mRc.top; i < m[0].mRc.bottom; i++)
	{
		//픽셀 컬러 속성에 따른 충돌 판정을 위해 만듦
		auto color = GetPixel(IMAGEMANAGER->findImage("배경3_c")->getMemDC(), m[0].mRc.left+30, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//바닥에 충돌한 경우
		if ((r == 0 && g == 0 && b == 0))
		{

			//이동할려는 위치가 나보다 많이 크지 않다면 
			if (m[0].bHeight - i <= 20) {
				cout << "충돌함, 충돌한 좌표 ->x : " << m[0].mRc.left + 30 << ", y : " << i << endl;
				cout << i << " - " << bHeight << " = " << i - bHeight << endl;
				//대상 이미지의 가장 겉의 라인을 따라가면서 움직일 수 있도록
				m[0].mRc.bottom = i + 5;
				m[0].mRc.top = m[0].mRc.bottom - 60;

				//이미지 끼리 닿인 부분의 색은
				//cout << "검사할 부분의 좌표는 -> x : " << rc2.left + 15 << "y : " << i << endl;
				cout << "r : " << r << "g : " << g << "b : " << b << "입니다." << endl;
				m[0].coll = true;
				m[0].floorCheck = true;
				break;
			}

		}
		//벽에 충돌한 경우
		else if ((r == 255 && g == 0 && b == 0))
		{
			if (m[0].floorOn)
			{
				//cout << "벽에 충돌함 ===============================" << endl;
				m[0].mRc.left = m[0].bFrameLeft;
				m[0].mRc.right = m[0].bFreameRight;
				m[0].coll = true;
				m[0].floorCheck = true;

			}
			else if (!m[0].floorOn)
			{
				//cout << "벽에 충돌함 ===============================" << endl;
				m[0].mRc.left = m[0].bFrameLeft;
				m[0].mRc.right = m[0].bFreameRight;
				m[0].coll = true;

			}

		}


	}

	//바닥인 상태에서 충돌하지 않았을 경우에 만약 내 밑 20 픽셀중에 땅이 있다면 추락하지 않음
	if (!m[0].coll && m[0].floorOn)
	{
		for (int i = m[0].mRc.bottom; i < m[0].mRc.bottom +20; i++)
		{
			//픽셀 컬러 속성에 따른 충돌 판정을 위해 만듦
			auto color = GetPixel(IMAGEMANAGER->findImage("배경3_c")->getMemDC(), m[0].mRc.left + 30, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			//이미지 끼리 닿인 부분이 마젠타 색상이 아닐 경우
			if (!(r == 255 & g == 0 & b == 255))
			{
				m[0].mRc.bottom = i + 5;
				m[0].mRc.top = m[0].mRc.bottom - 60;
				cout << "밑에 땅이 가까이 있기 때문에 추락하지 않음 " << endl;
				m[0].floorCheck = true;
				break;
			}
		}
	}

	RECT tempRect;

	for (int i = 0; i < 2; i++)
	{
		//테투리만 겹쳐서는 충돌이 안됨! ->speed만큼 겹친 부분이 존재
		if (IntersectRect(&tempRect, &rc2, &m[0].mRc) && !m[0].steMode)
		{
			m[0].state = 2;
			m[0].attackOn = true;
			m[0].monsterImg = IMAGEMANAGER->findImage("skel_attack");
		}

	}
	

	if (m[0].floorCheck)
	{
		m[0].floorOn = true;
		cout << "바닥임" << endl;
	}
	else if (!m[0].floorCheck)
	{
		m[0].floorOn = false;
		cout << "충돌 안 함, 내 좌표 ->x : " << rc2.left << ", y : " << rc2.bottom << endl;
		cout << "바닥이 아님" << endl;
	}


	//바닥이 아니고 점프 중이 아니라면 
	if (!m[0].floorOn)
	{
		m[0].mRc.top += 5;
		m[0].mRc.bottom += 5;
		m[0].landing = 1;
		cout << "추락함" << endl;

	}

	if (m[0].landing == 1 && m[0].floorOn)
	{
	
		m[0].landing = 0;

	}

	//cout << "이번 플레이어 rc의 좌표 : " << rc.left << " , " << rc.bottom << endl;
	//cout << "이번 플레이어 rc2의 좌표 : " << rc2.left << " , " << rc2.bottom << endl;
	
	if (m[0].coll)
	{
		cout << "이번 업데이트에서는 충돌함 " << endl;
	}


	cout << endl;



	m[0].bFrameLeft = m[0].mRc.left;
	m[0].bFreameRight = m[0].mRc.right;
	m[0].bHeight = m[0].mRc.bottom;




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

	//플레이어 이미지
	rc = RectMakeCenter(_x, _y, 60, 60);
	//플레이어 충돌체
	rc2 = RectMake(rc.left + 30, rc.top, 60, 60);

	_probeY = rc2.top + player->getHeight() / 2;
	bHeight = rc2.bottom;
	cout << player->getHeight() / 4 << endl;
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


	m[0].mRc = RectMake(800, 100, 60, 60);


	m[0].monsterImg = IMAGEMANAGER->findImage("skel_idle");
	m[0].monsterImg->setFrameX(0);
	m[0].monsterImg->setFrameY(0);
	m[0].state = 0;
	m[0].dy = 0;






}
