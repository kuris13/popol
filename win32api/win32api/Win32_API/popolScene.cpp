#include "setDefine.h"
#include "popolScene.h"
#include  <cassert>



HRESULT popolScene::init()
{

	playerS->backName = "배경3_c";


	if (playerS->nowScene == 2)
	{
		
		playerS->rc = RectMake(WINSIZE_X-90, 600, 60, 60);
	}
	else {
		playerS->rc = RectMake(50, 600, 60, 60);

	}
	playerS->nowScene = 1;
	player2 = playerS;
	
	//==========================================
	//==========================================
	for (int i = 0; i < monsterCount; i++)
	{
		m[i] = new monster();

		m[i]->monsterInit();
		m[i]->playerRect = &player2->rc2;
		m[i]->backName = "배경3_c";

	}

	m[0]->setLocation(600, 500);
	m[1]->setLocation(1000,500);

	coinImg = IMAGEMANAGER->findImage("coin");
	coinImg->setFrameY(0);
	return S_OK;
}

void popolScene::release()
{
}

void popolScene::update()
{

	//플레이어와 몬스터의 충돌 처리
	//플레이어에게 몬스터의 정보 입력 -> 몬스터와의 충돌 처리에 사용
	player2->monstCount = monsterCount;

	for (int i = 0; i < monsterCount; i++)
	{
		


		player2->mRc[i] = m[i]->mRc;
		
		if (m[i]->state == 2)
		{
			player2->isMonsterAttack[i] = true;
		}
		else
		{
			player2->isMonsterAttack[i] = false;
		}
	}

	//====================================================
	//필드 드랍 아이템 획득 -> 퀵슬롯으로 이동
	RECT temp5;
	for (int i = 0; i < STAGEMANAGER->stageOne->stageItemVec.size(); i++)
	{
		if (IntersectRect(&temp5, &playerS->rc2, &STAGEMANAGER->stageOne->stageItem[i]))
		{
			SOUNDMANAGER->play("coin1");
			//처리된 아이템은 화면밖으로 이동
			STAGEMANAGER->stageOne->stageItem[i].left = -100;
			STAGEMANAGER->stageOne->stageItem[i].right = -100;

			//플레이어의 인벤토리에 아이템 푸시
			player2->invenVec2.push_back(STAGEMANAGER->stageOne->stageItemVec.at(i));
			cout << "x";
		}

	}
	RECT temp6;
	for (int i = 0; i < STAGEMANAGER->stageOne->coin; i++)
	{
		if (IntersectRect(&temp6, &playerS->rc2, &STAGEMANAGER->stageOne->coinRect[i]))
		{
			SOUNDMANAGER->play("coin2");
			//처리된 아이템은 화면밖으로 이동
			STAGEMANAGER->stageOne->coinRect[i].left = -100;
			STAGEMANAGER->stageOne->coinRect[i].right = -100;
			cout << "z";
			++playerS->score;
			
		}

	}


	//다음 맵으로 이동
	player2->playerMovement();
	if (player2->rc2.right > WINSIZE_X)
	{
		SCENEMANAGER->changeScene("포폴2");

	}
	//=========================================

	for (int i = 0; i < monsterCount; i++)
	{
		m[i]->monsterMoveMent();
	}


	//==============================================
	//방향 화살표
	_alpha -= 3.0f;

	if (_alpha <= 0)
	{
		_alpha = 255;
	}
	//===============================================

	//coin움직임
	coinImg->setFrameX(coinState++ / 5);

	if (coinState > 30) coinState = 0;


	SOUNDMANAGER->update();

}

void popolScene::render()
{

	IMAGEMANAGER->render("뒷배경1", getMemDC());
	IMAGEMANAGER->render("뒷배경2", getMemDC());
	IMAGEMANAGER->render("뒷배경3", getMemDC());


	IMAGEMANAGER->render("배경3", getMemDC(), IMAGEMANAGER->findImage("배경3")->getX(), IMAGEMANAGER->findImage("배경3")->getY());

	for (int i = 0; i < player2->lifeCount; i++)
	{
		IMAGEMANAGER->render("체력", getMemDC(),30+i*55,50);
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
		IMAGEMANAGER->render(playerS->invenVec2.at(i), getMemDC(), 700+4 + i * 62, 54);
		
	}
	
	for (int i = 0; i < STAGEMANAGER->stageOne->stageItemVec.size(); i++)
	{
			IMAGEMANAGER->render(STAGEMANAGER->stageOne->stageItemVec.at(i), getMemDC(), STAGEMANAGER->stageOne->stageItem[i].left, STAGEMANAGER->stageOne->stageItem[i].top);
	}


	IMAGEMANAGER->frameRender("coin", getMemDC(), STAGEMANAGER->stageOne->coinRect[0].left, STAGEMANAGER->stageOne->coinRect[0].top);
	

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
		IMAGEMANAGER->render("1coin", getMemDC(), 280 + (i-15) * 10, 65);

	}

	for (int i = 30; i < playerS->score; i++)
	{
		if (i > 45)
		{
			break;
		}
		IMAGEMANAGER->render("1coin", getMemDC(), 280 + (i-30) * 10, 80);

	}
	

	for (int i = 0; i < playerS->haveitem.size(); i++)
	{
			IMAGEMANAGER->render(playerS->haveitem.at(i), getMemDC(), 30 + i * 55, 150);
		
	}



	RectangleMake(getMemDC(), m[0]->mRc);
	/*

	//RectangleMake(getMemDC(), rc);
	RectangleMake(getMemDC(),playerS->rc2);
	

	if (player2.attackOn)
	{
		auto brush = CreateSolidBrush(RGB(255, 0, 0));
		FillRect(getMemDC(), &rc2, brush);
		DeleteObject(brush);
	}
	else if (player2.rollOn)
	{
		auto brush = CreateSolidBrush(RGB(0, 255, 0));
		FillRect(getMemDC(), &rc2, brush);
		DeleteObject(brush);
	}
	*/
	if (player2->deathOn) {
		IMAGEMANAGER->frameRender("p_death", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 0)
	{
		IMAGEMANAGER->frameRender("p_idle", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 1)
	{
		IMAGEMANAGER->frameRender("p_run", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 2)
	{
		IMAGEMANAGER->frameRender("p_attack", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 3)
	{
		IMAGEMANAGER->frameRender("p_jump", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 4)
	{
		IMAGEMANAGER->frameRender("p_roll", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 5)
	{
		IMAGEMANAGER->frameRender("p_fall", getMemDC(), player2->rc.left, player2->rc.top);
	}
	else if (player2->state == 6)
	{
		IMAGEMANAGER->frameRender("p_hit", getMemDC(), player2->rc.left, player2->rc.top);
	}


	

	
	for (int i = 0; i < monsterCount; i++)
	{
		if (m[i]->deathOn)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_death");
			m[i]->monsterImg->setFrameX(m[i]->deathState/5);
			IMAGEMANAGER->frameRender("skel_death", getMemDC(), m[i]->mRc.left-24, m[i]->mRc.top);
		}else if (m[i]->state == 0)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_idle");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_idle", getMemDC(), m[i]->mRc.left-24, m[i]->mRc.top);

		}
		else if (m[i]->state == 1)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_walk");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_walk", getMemDC(), m[i]->mRc.left-24, m[i]->mRc.top);

		}
		else if (m[i]->state == 2)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_attack");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_attack", getMemDC(), m[i]->mRc.left-24, m[i]->mRc.top-10);

		}
		else if (m[i]->state == 3)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_hit");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_hit", getMemDC(), m[i]->mRc.left-24, m[i]->mRc.top);
		}
 
	}
	


	
	//RectangleMake(getMemDC(), foothold[0]);
//	RectangleMake(getMemDC(), foothold[1]);
	//RectangleMake(getMemDC(), foothold[2]);

	//RectangleMake(getMemDC(), m[0].mRc);
	//RectangleMake(getMemDC(), m[1].mRc);

	//RectangleMake(getMemDC(), cameraPoint1);

	//IMAGEMANAGER->alphaRender("화살표", getMemDC(), WINSIZE_X - 75, WINSIZE_Y / 2 - 40, _alpha);


	sprintf(str, "마우스 좌표 x : %d , y : %d ", _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
	
	
}
