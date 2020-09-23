#include "setDefine.h"
#include "player.h"


void player::playerInit()
{




	playerImg = IMAGEMANAGER->findImage("p_idle");

	_x = 0;
	_y = 0;

	//플레이어 이미지
	rc = RectMakeCenter(_x, _y, 60, 60);
	//플레이어 충돌체
	rc2 = RectMake(rc.left + 30, rc.top, 60, 60);

	_probeY = rc2.top + playerImg->getHeight() / 2;
	bHeight = rc2.bottom;

	lifeCount = 4;
	bFrameLeft = rc.left;



}
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
					rc.left += runSpeed;
					rc.right += runSpeed;

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
					rc.left -= runSpeed;
					rc.right -= runSpeed;
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
					//공격
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


				//점프
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
			playerImg->setFrameX(rollState++/3);
			if (dy == 0)
			{
				rc.left += rollSpeed;
				rc.right += rollSpeed;
			}
			else if (dy == 1)
			{
				rc.left -= rollSpeed;
				rc.right -= rollSpeed;
			}
		}
		if (hitOn)
		{
			playerImg = IMAGEMANAGER->findImage("p_hit");
			playerImg->setFrameX(hitState++ / 10);
			playerImg->setFrameY(dy);
			//hit상태
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

		if (jumpGa >= maxJump)
		{
			jumpState = 0;
			jumpGa = 0;
			jumpOn = false;
			state = 0;
			playerImg = IMAGEMANAGER->findImage("p_idle");
			playerImg->setFrameY(dy);

		}
		if (rollState > 36)
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

		//몬스터의 수많큼 반복 
		for (int i = 0; i < monstCount; i++)
		{

			//테투리만 겹쳐서는 충돌이 안됨! ->speed만큼 겹친 부분이 존재
			if (IntersectRect(&tempRect, &rc2, &mRc[i]) && !hitOn &&isMonsterAttack[i] && !attackOn && !noHitMode)
			{
				//내가 회피중이 아닐 때 몬스터와 충돌한다면
				if (!rollOn && ((IMAGEMANAGER->findImage("skel_attack")->getFrameX() > 7) && (IMAGEMANAGER->findImage("skel_attack")->getFrameX() < 12)))
				{
					hitOn = true;
					noHitMode = true;
					hitMonNum = i;

					--lifeCount;

					//내가 몬스터보다 오른쪽에 있다면 
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


	//	CAMERA = rc.left - bFrameLeft;
		bFrameLeft = rc.left;
		bFreameRight = rc.right;
		bHeight = rc.bottom;


	}

}


void player::useItem()
{

	if (invenVec2.size() > 0)
	{
		if (invenVec2.at(0) == "물고기")
		{
			maxJump += 100;
			haveitem.push_back("물고기");

		}else if (invenVec2.at(0) == "포도")
		{
			runSpeed += 2;
			haveitem.push_back("포도");
		}
		else if (invenVec2.at(0) == "food")
		{
			rollSpeed += 5;
			haveitem.push_back("food");
		}
		else if (invenVec2.at(0) == "체력")
		{

			 if(lifeCount <4) lifeCount += 1;
		}

		invenVec2.erase(invenVec2.begin());
	}

	





}


