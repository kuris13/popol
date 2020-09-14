#include "setDefine.h"
#include "popolScene.h"




HRESULT popolScene::init()
{
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


	if (m[0].state == 0)
	{
		IMAGEMANAGER->frameRender("skel_idle", getMemDC(), m[0].mRc.left, m[0].mRc.top);

	}
	
	//RectangleMake(getMemDC(), foothold[0]);
//	RectangleMake(getMemDC(), foothold[1]);
	//RectangleMake(getMemDC(), foothold[2]);

	sprintf(str, "마우스 좌표 x : %d , y : %d       fall :  %d    jump : %d   state : %d   landing : %d", _ptMouse.x, _ptMouse.y,floorOn,jumpOn, state, landing);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
	
	
}

void popolScene::playerMovement()
{
	cout << "업데이트 시작 좌표 y :" << rc2.bottom << endl;

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

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (!jumpOn && !attackOn && !rollOn)
		{
			state = 0;

			player = IMAGEMANAGER->findImage("p_idle");
			player->setFrameY(dy);
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
	cout << "충돌 직전 value 측정 " << endl;
	cout << "==============================================" << endl;
	cout << "rc의 bottom값 : " << rc.bottom << " rc2의 bottom값 : " << rc2.bottom << endl;
	cout << "_probeY (이미지 중간 값)의 값 : " << _probeY << endl;
	cout << "==============================================" << endl;

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

	/*
	//벽 충돌
	if (!floorOn && !jumpOn)
	{
		cout << "추락 중에 왼쪽 아래 모서리가 벽에 닿음" << endl;
		//왼쪽 아래 모서리가 벽에 닿으면 안 움직임
		auto color = GetPixel(IMAGEMANAGER->findImage("배경3")->getMemDC(), rc2.left, rc2.bottom);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//이미지 끼리 닿인 부분이 마젠타 색상이 아닐 경우
		if (!(r == 255 & g == 0 & b == 255))
		{
			rc.left = bFrameLeft;
			rc.right = bFreameRight;
		}
	}
	*/

	/*
	floorCheck = false;
	RECT tempRect;

	for (int i = 0; i < 2; i++)
	{
		//테투리만 겹쳐서는 충돌이 안됨! ->speed만큼 겹친 부분이 존재
		if (IntersectRect(&tempRect, &rc2, &foothold[i]))
		{
			cout << i << "번과 충돌" << endl;
			cout <<"   나의 rect 값->         left : "<<rc.left<<" , right : "<<rc.right <<", top : "<<rc.top<<", bottom : "<<rc.bottom << endl
				 <<",  충돌한 물체의 좌표값-> left : "<< foothold[i].left<<", right : "<<foothold[i].right <<", top : "<<foothold[i].top
				 <<", bottom : "<<foothold[i].bottom <<endl;

			if (rc2.left <= foothold[i].right && rc2.right >= foothold[i].right && rc2.bottom-6 >= foothold[i].top)
			{

				//왼쪽으로 이동한다면 전 프레임의 위치로 이동 (이동 x)
				if (rc.left < bFrameLeft)
				{
					rc.left = bFrameLeft;
					rc.right = bFreameRight;
				}

				//rc2.left = foothold[i].right;
				//rc2.right = rc2.left + 60;
				cout << "왼쪽으로 충돌" << endl;
			}

			//rc2의 바닥이 충돌 했을 경우
			if (rc2.bottom == foothold[i].top+5 && rc.top < foothold[i].top)
			{
				rc.bottom = foothold[i].top+5;
				rc.top = rc.bottom - 60;
				cout << "발이 충돌" << endl;

				floorCheck = true;


			}
		}

	}
	*/

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

	cout << "이번 플레이어 rc의 좌표 : " << rc.left << " , " << rc.bottom << endl;
	cout << "이번 플레이어 rc2의 좌표 : " << rc2.left << " , " << rc2.bottom << endl;
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

	
	//플레이어가 몬스터 오른쪽에 있음
	if ((rc2.left + 30) - (m[0].mRc.left + 30) > 0)
	{
		m[0].mRc.left += 2;
		m[0].mRc.right += 2;
		m[0].dy = 0;

	}
	//플레이어가 몬스터 왼쪽에 있음
	else {
		m[0].mRc.left -= 2;
		m[0].mRc.right -= 2;
		m[0].dy = 1;
	}





	//대기 상태라면
	if (m[0].state == 0)
	{
		m[0].monsterImg->setFrameY(m[0].dy);
		m[0].monsterImg->setFrameX(idleState++ / 5);
	}

	if (m[0].attackOn)
	{
		m[0].monsterImg->setFrameY(m[0].dy);
		m[0].monsterImg->setFrameX(attackState++ / 5);
	}
	//hit, death 추가해야함
	



	if (m[0].idleState > 90)
	{
		m[0].idleState = 0;
	}

	if (m[0].runState > 40)
	{
		m[0].runState = 0;
	}

	if (m[0].attackState > 110)
	{
		m[0].attackState = 0;
		m[0].attackOn = false;
		m[0].state = 0;
		m[0].monsterImg = IMAGEMANAGER->findImage("p_idle");
		m[0].monsterImg->setFrameY(dy);
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

	/*
	//벽 충돌
	if (!floorOn && !jumpOn)
	{
		cout << "추락 중에 왼쪽 아래 모서리가 벽에 닿음" << endl;
		//왼쪽 아래 모서리가 벽에 닿으면 안 움직임
		auto color = GetPixel(IMAGEMANAGER->findImage("배경3")->getMemDC(), rc2.left, rc2.bottom);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//이미지 끼리 닿인 부분이 마젠타 색상이 아닐 경우
		if (!(r == 255 & g == 0 & b == 255))
		{
			rc.left = bFrameLeft;
			rc.right = bFreameRight;
		}
	}
	*/

	/*
	floorCheck = false;
	RECT tempRect;

	for (int i = 0; i < 2; i++)
	{
		//테투리만 겹쳐서는 충돌이 안됨! ->speed만큼 겹친 부분이 존재
		if (IntersectRect(&tempRect, &rc2, &foothold[i]))
		{
			cout << i << "번과 충돌" << endl;
			cout <<"   나의 rect 값->         left : "<<rc.left<<" , right : "<<rc.right <<", top : "<<rc.top<<", bottom : "<<rc.bottom << endl
				 <<",  충돌한 물체의 좌표값-> left : "<< foothold[i].left<<", right : "<<foothold[i].right <<", top : "<<foothold[i].top
				 <<", bottom : "<<foothold[i].bottom <<endl;

			if (rc2.left <= foothold[i].right && rc2.right >= foothold[i].right && rc2.bottom-6 >= foothold[i].top)
			{

				//왼쪽으로 이동한다면 전 프레임의 위치로 이동 (이동 x)
				if (rc.left < bFrameLeft)
				{
					rc.left = bFrameLeft;
					rc.right = bFreameRight;
				}

				//rc2.left = foothold[i].right;
				//rc2.right = rc2.left + 60;
				cout << "왼쪽으로 충돌" << endl;
			}

			//rc2의 바닥이 충돌 했을 경우
			if (rc2.bottom == foothold[i].top+5 && rc.top < foothold[i].top)
			{
				rc.bottom = foothold[i].top+5;
				rc.top = rc.bottom - 60;
				cout << "발이 충돌" << endl;

				floorCheck = true;


			}
		}

	}
	*/

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
	IMAGEMANAGER->addImage("배경3", "Images/first_p.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경3_c", "Images/first_c.bmp", 1312, 768, true, RGB(255, 0, 255));


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

	IMAGEMANAGER->addFrameImage("p_landing", "Images/player/landing.bmp",
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
