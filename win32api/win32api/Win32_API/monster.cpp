#include "setDefine.h"
#include "monster.h"
#include "player.h"
void monster::monsterInit()
{

	IMAGEMANAGER->addFrameImage("skel_idle", "Images/skel/idle.bmp", 1144, 128, 11, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_attack", "Images/skel/attack.bmp", 1872, 148, 18, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_death", "Images/skel/death.bmp", 1560, 128, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_walk", "Images/skel/walk.bmp", 1352, 128, 13, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("skel_hit", "Images/skel/hit.bmp", 832, 128, 8, 2, true, RGB(255, 0, 255));

	
	for (int i = 0; i < 2; i++)
	{

		

		monsterImg = IMAGEMANAGER->findImage("skel_idle");


		monsterImg->setFrameX(0);
		monsterImg->setFrameY(0);


		state = 0;
		dy = 0;

	}

	

}

void monster::monsterMoveMent()
{

	if (deathOn)
	{
		
		monsterImg->setFrameX(deathState++ / 5);

		if (deathState > 75)
		{

		}
	}else if (!deathOn) {
		//cout << "몬스터의 위치 " << mRc.left + 30 << endl;
		if (!steMode && !attackOn)
		{
			//몬스터가 왼쪽
			if ((playerRect->left + 30) - (mRc.left + 30) > 2)
			{
				mRc.left += 2;
				mRc.right += 2;
				dy = 0;

				state = 1;

				monsterImg = IMAGEMANAGER->findImage("skel_walk");
				monsterImg->setFrameY(dy);
				monsterImg->setFrameX(runState++ / 5);

				ste += 1;


			}
			
			//플레이어가 몬스터 왼쪽에 있음
			else if ((playerRect->left + 30) - (mRc.left + 30) < 2)
			{
				mRc.left -= 2;
				mRc.right -= 2;
				dy = 1;

				state = 1;

				monsterImg = IMAGEMANAGER->findImage("skel_walk");
				monsterImg->setFrameY(dy);
				monsterImg->setFrameX(runState++ / 5);
				ste += 1;

			}
			else
			{
				//
			}

		}


		//대기 상태라면
		if (state == 0)
		{
			monsterImg->setFrameY(dy);
			monsterImg->setFrameX(idleState++ / 5);
			if (ste > 0)
			{
				ste -= 1;
			}

			if (ste == 0)
			{
				steMode = false;
			}

		}

		if (attackOn)
		{

			monsterImg->setFrameY(dy);
			monsterImg->setFrameX(attackState++ / 5);
			ste += 1;
		}

		if (hitOn)
		{
			monsterImg->setFrameY(dy);
			monsterImg->setFrameX(hitState++ / 5);
		}

		//death 추가해야함


		if (idleState > 90)
		{
			idleState = 0;
		}

		if (runState > 60)
		{
			runState = 0;
		}

		if (attackState > 90)
		{
			attackState = 0;
			attackOn = false;
			state = 0;
			monsterImg = IMAGEMANAGER->findImage("skel_idle");
			monsterImg->setFrameY(dy);
		}

		if (ste > 400 && !attackOn)
		{
			state = 0;
			monsterImg = IMAGEMANAGER->findImage("skel_idle");
			monsterImg->setFrameY(dy);
			steMode = true;
		}

		if (hitState > 40)
		{
			hitState = 0;
			hitOn = false;
			state = 0;
			monsterImg = IMAGEMANAGER->findImage("skel_idle");
			monsterImg->setFrameY(dy);
			--monLife;
			if (monLife == 0)
			{
				deathOn = true;
				monsterImg = IMAGEMANAGER->findImage("skel_death");
			}

		}





		floorCheck = false;
		coll = false;

		//몬스터 픽셀 충돌

		//바닥 충돌
		for (int j = mRc.top; j < mRc.bottom; j++)
		{
			//픽셀 컬러 속성에 따른 충돌 판정을 위해 만듦
			auto color = GetPixel(IMAGEMANAGER->findImage("배경3_c")->getMemDC(), mRc.left + 30, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			//바닥에 충돌한 경우
			if ((r == 0 && g == 0 && b == 0))
			{

				//이동할려는 위치가 나보다 많이 크지 않다면 
				if (bHeight - j <= 20) {
					//대상 이미지의 가장 겉의 라인을 따라가면서 움직일 수 있도록
					mRc.bottom = j + 5;
					mRc.top = mRc.bottom - 60;

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
					mRc.left = bFrameLeft;
					mRc.right = bFreameRight;
					coll = true;
					floorCheck = true;

				}
				else if (!floorOn)
				{
					mRc.left = bFrameLeft;
					mRc.right = bFreameRight;
					coll = true;

				}

			}


		}

		//바닥인 상태에서 충돌하지 않았을 경우에 만약 내 밑 20 픽셀중에 땅이 있다면 추락하지 않음
		if (!coll && floorOn)
		{
			for (int j = mRc.bottom; j < mRc.bottom + 20; j++)
			{
				//픽셀 컬러 속성에 따른 충돌 판정을 위해 만듦
				auto color = GetPixel(IMAGEMANAGER->findImage("배경3_c")->getMemDC(), mRc.left + 30, j);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				//이미지 끼리 닿인 부분이 마젠타 색상이 아닐 경우
				if (!(r == 255 & g == 0 & b == 255))
				{
					mRc.bottom = j + 5;
					mRc.top = mRc.bottom - 60;
					floorCheck = true;
					break;
				}
			}
		}


		RECT tempRect;

		for (int j = 0; j < 2; j++)
		{

			//내가 공격중이 아닐 때
			if (IntersectRect(&tempRect, playerRect, &mRc) && !attackOn  &&playerS->attackOn)
			{
				//피격
				state = 3;
				hitOn = true;
				monsterImg = IMAGEMANAGER->findImage("skel_hit");
				
			}
			else if (IntersectRect(&tempRect, playerRect, &mRc) && !steMode && !hitOn)
			{
				//공격
				state = 2;
				attackOn = true;
				monsterImg = IMAGEMANAGER->findImage("skel_attack");

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
		if (!floorOn)
		{
			mRc.top += 5;
			mRc.bottom += 5;
			landing = 1;

		}

		if (landing == 1 && floorOn)
		{

			landing = 0;

		}


		if (coll)
		{
		}





		bFrameLeft = mRc.left;
		bFreameRight = mRc.right;
		bHeight = mRc.bottom;
	}
}

void monster::setLocation(int x, int y)
{

	mRc = RectMake(x , y, 60, 60);

}

