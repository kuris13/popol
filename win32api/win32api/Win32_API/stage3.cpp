#include "setDefine.h"
#include "stage3.h"

HRESULT stage3::init()
{
	IMAGEMANAGER->addImage("stage3", "Images/stage3.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage3_c", "Images/stage3_c.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));



	//==========================================
	playerS->backName = "stage3_c";

	playerS->nowScene = 3;
	playerS->rc = RectMake(50, 530, 60, 60);
	//==========================================


	for (int i = 0; i < monsterCount; i++)
	{
		m[i] = new monster();

		m[i]->monsterInit();
		m[i]->playerRect = &playerS->rc2;
		m[i]->backName = "stage3_c";
	}


	m[0]->setLocation(450, 600);
	m[1]->setLocation(1000, 600);
	


	coinImg = IMAGEMANAGER->findImage("coin");
	coinImg->setFrameY(0);


	return S_OK;
}

void stage3::release()
{
}

void stage3::update()
{

	if (playerS->rc2.left < 0)
	{
		SCENEMANAGER->changeScene("포폴2");
	}

	playerS->monstCount = monsterCount;

	for (int i = 0; i < monsterCount; i++)
	{

		playerS->mRc[i] = m[i]->mRc;

		if (m[i]->state == 2)
		{
			playerS->isMonsterAttack[i] = true;
		}
		else
		{
			playerS->isMonsterAttack[i] = false;
		}
	}

	
	//====================================================
	//필드 드랍 아이템 획득 -> 퀵슬롯으로 이동
	RECT temp5;
	for (int i = 0; i < STAGEMANAGER->stageThr->stageItemVec.size(); i++)
	{
		if (IntersectRect(&temp5, &playerS->rc2, &STAGEMANAGER->stageThr->stageItem[i]))
		{
			//처리된 아이템은 화면밖으로 이동
			STAGEMANAGER->stageThr->stageItem[i].left = -100;
			STAGEMANAGER->stageThr->stageItem[i].right = -100;

			//플레이어의 인벤토리에 아이템 푸시
			playerS->invenVec2.push_back(STAGEMANAGER->stageThr->stageItemVec.at(i));
		}

	}

	RECT temp6;
	for (int i = 0; i < STAGEMANAGER->stageThr->coin; i++)
	{
		if (IntersectRect(&temp6, &playerS->rc2, &STAGEMANAGER->stageThr->coinRect[i]))
		{
			//처리된 아이템은 화면밖으로 이동
			STAGEMANAGER->stageThr->coinRect[i].left = -100;
			STAGEMANAGER->stageThr->coinRect[i].right = -100;
			++playerS->score;

		}

	} 

	

	playerS->playerMovement();


	//다음 맵으로 이동
	if (playerS->rc2.right > WINSIZE_X)
	{
		//SCENEMANAGER->changeScene("포폴3");

	}

	for (int i = 0; i < monsterCount; i++)
	{
		m[i]->monsterMoveMent();
	}

	//coin움직임
	coinImg->setFrameX(coinState++ / 5);

	if (coinState > 30) coinState = 0;

}

void stage3::render()
{

	IMAGEMANAGER->render("뒷배경1", getMemDC());
	IMAGEMANAGER->render("뒷배경2", getMemDC());
	IMAGEMANAGER->render("뒷배경3", getMemDC());

	IMAGEMANAGER->render("stage3", getMemDC());



	
	
	//========================================================================
	for (int i = 0; i < playerS->lifeCount; i++)
	{
		IMAGEMANAGER->render("체력", getMemDC(), 30 + i * 55, 50);
	}

	for (int i = 0; i < 4; i++)
	{

		IMAGEMANAGER->render("itemBack", getMemDC(), 700 + i * 62, 50);
	}

	for (int i = 0; i < playerS->invenVec2.size(); i++)
	{
		if (i == 4)
		{
			break;
		}
		IMAGEMANAGER->render(playerS->invenVec2.at(i), getMemDC(), 700 + 4 + i * 62, 54);

	}

	for (int i = 0; i < STAGEMANAGER->stageThr->stageItemVec.size(); i++)
	{
		IMAGEMANAGER->render(STAGEMANAGER->stageThr->stageItemVec.at(i), getMemDC(), STAGEMANAGER->stageThr->stageItem[i].left, STAGEMANAGER->stageThr->stageItem[i].top);
	}

	for (int i = 0; i < STAGEMANAGER->stageThr->coin; i++)
	{
		IMAGEMANAGER->frameRender("coin", getMemDC(), STAGEMANAGER->stageThr->coinRect[i].left, STAGEMANAGER->stageThr->coinRect[i].top);

	}


	for (int i = 0; i < playerS->score; i++)
	{
		if (i > 15)
		{
			break;
		}
		IMAGEMANAGER->render("1coin", getMemDC(), 280 + i * 10, 50);

	}

	for (int i = 15; i < playerS->score; i++)
	{
		if (i > 30)
		{
			break;
		}
		IMAGEMANAGER->render("1coin", getMemDC(), 280 + (i - 15) * 10, 65);

	}

	for (int i = 30; i < playerS->score; i++)
	{
		if (i > 45)
		{
			break;
		}
		IMAGEMANAGER->render("1coin", getMemDC(), 280 + (i - 30) * 10, 80);

	}


	for (int i = 0; i < playerS->haveitem.size(); i++)
	{
		IMAGEMANAGER->render(playerS->haveitem.at(i), getMemDC(), 30 + i * 55, 150);

	}
	//========================================================================

	


	


	if (playerS->state == 0)
	{
		IMAGEMANAGER->frameRender("p_idle", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 1)
	{
		IMAGEMANAGER->frameRender("p_run", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 2)
	{
		IMAGEMANAGER->frameRender("p_attack", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 3)
	{
		IMAGEMANAGER->frameRender("p_jump", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 4)
	{
		IMAGEMANAGER->frameRender("p_roll", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 5)
	{
		IMAGEMANAGER->frameRender("p_fall", getMemDC(), playerS->rc.left, playerS->rc.top);
	}
	else if (playerS->state == 6)
	{
		IMAGEMANAGER->frameRender("p_hit", getMemDC(), playerS->rc.left, playerS->rc.top);
	}


	for (int i = 0; i < monsterCount; i++)
	{
		if (m[i]->deathOn)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_death");
			m[i]->monsterImg->setFrameX(m[i]->deathState / 5);
			IMAGEMANAGER->frameRender("skel_death", getMemDC(), m[i]->mRc.left - 24, m[i]->mRc.top);
		}
		else if (m[i]->state == 0)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_idle");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_idle", getMemDC(), m[i]->mRc.left - 24, m[i]->mRc.top);

		}
		else if (m[i]->state == 1)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_walk");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_walk", getMemDC(), m[i]->mRc.left - 24, m[i]->mRc.top);

		}
		else if (m[i]->state == 2)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_attack");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_attack", getMemDC(), m[i]->mRc.left - 24, m[i]->mRc.top - 10);

		}
		else if (m[i]->state == 3)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_hit");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_hit", getMemDC(), m[i]->mRc.left - 24, m[i]->mRc.top);
		}

	}
	sprintf(str, "마우스 좌표 x : %d , y : %d ", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 10, 10, str, strlen(str));

}
