#include "setDefine.h"
#include "monster.h"

void monster::monsterInit()
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



		monsterImg = IMAGEMANAGER->findImage("skel_idle");
		monsterImg->setFrameX(0);
		monsterImg->setFrameY(0);


		state = 0;
		dy = 0;

	}

	

}

void monster::monsterMoveMent()
{
	for (int i = 0; i < 2; i++)
	{
		
		if (!steMode && !attackOn)
		{
			//���Ͱ� ����
			if ((playerRect->left + 30) - (mRc.left + 30) > 0)
			{
				mRc.left += 2;
				mRc.right += 2;
				dy = 0;

				state = 1;

				monsterImg = IMAGEMANAGER->findImage("skel_walk");
				monsterImg->setFrameY(dy);
				monsterImg->setFrameX(runState++ / 5);


				ste += 1;

				cout << i << "�� ���ʹ� �÷��̾� ���ʿ� ����, ������ ����" <<dy << endl;

			}
			else if ((playerRect->left + 30) - (mRc.left + 30) == 0)
			{
				//
			}
			//�÷��̾ ���� ���ʿ� ����
			else if ((playerRect->left + 30) - (mRc.left + 30) < 0) {
				mRc.left -= 2;
				mRc.right -= 2;
				dy = 1;

				state = 1;

				monsterImg = IMAGEMANAGER->findImage("skel_walk");
				monsterImg->setFrameY(dy);
				monsterImg->setFrameX(runState++ / 5);

				ste += 1;
				cout << i << "�� ���ʹ� �÷��̾� �����ʿ� ����, ������ ����" << dy << endl;
			}

		}
		
		cout << endl;




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
		//hit, death �߰��ؾ���




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

		if (ste > 300 && !attackOn)
		{
			state = 0;
			monsterImg = IMAGEMANAGER->findImage("skel_idle");
			monsterImg->setFrameY(dy);
			steMode = true;
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
		/*
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
		*/

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



	//cout << "�̹� " << 0 << "�� ° ������ ������ " << m[0].dy << endl;
	//cout << "�̹� " << 1 << "�� ° ������ ������ " << m[1].dy << endl;

	cout << endl;


}

void monster::setLocation(int x, int y)
{

	mRc = RectMake(x , y, 60, 60);

}
