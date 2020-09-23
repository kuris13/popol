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
		//cout << "������ ��ġ " << mRc.left + 30 << endl;
		if (!steMode && !attackOn)
		{
			//���Ͱ� ����
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
			
			//�÷��̾ ���� ���ʿ� ����
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


		//��� ���¶��
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

		//death �߰��ؾ���


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

		//���� �ȼ� �浹

		//�ٴ� �浹
		for (int j = mRc.top; j < mRc.bottom; j++)
		{
			//�ȼ� �÷� �Ӽ��� ���� �浹 ������ ���� ����
			auto color = GetPixel(IMAGEMANAGER->findImage("���3_c")->getMemDC(), mRc.left + 30, j);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			//�ٴڿ� �浹�� ���
			if ((r == 0 && g == 0 && b == 0))
			{

				//�̵��ҷ��� ��ġ�� ������ ���� ũ�� �ʴٸ� 
				if (bHeight - j <= 20) {
					//��� �̹����� ���� ���� ������ ���󰡸鼭 ������ �� �ֵ���
					mRc.bottom = j + 5;
					mRc.top = mRc.bottom - 60;

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

		//�ٴ��� ���¿��� �浹���� �ʾ��� ��쿡 ���� �� �� 20 �ȼ��߿� ���� �ִٸ� �߶����� ����
		if (!coll && floorOn)
		{
			for (int j = mRc.bottom; j < mRc.bottom + 20; j++)
			{
				//�ȼ� �÷� �Ӽ��� ���� �浹 ������ ���� ����
				auto color = GetPixel(IMAGEMANAGER->findImage("���3_c")->getMemDC(), mRc.left + 30, j);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				//�̹��� ���� ���� �κ��� ����Ÿ ������ �ƴ� ���
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

			//���� �������� �ƴ� ��
			if (IntersectRect(&tempRect, playerRect, &mRc) && !attackOn  &&playerS->attackOn)
			{
				//�ǰ�
				state = 3;
				hitOn = true;
				monsterImg = IMAGEMANAGER->findImage("skel_hit");
				
			}
			else if (IntersectRect(&tempRect, playerRect, &mRc) && !steMode && !hitOn)
			{
				//����
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


		//�ٴ��� �ƴϰ� ���� ���� �ƴ϶�� 
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

