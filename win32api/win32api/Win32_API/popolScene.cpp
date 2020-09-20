#include "setDefine.h"
#include "popolScene.h"




HRESULT popolScene::init()
{
	//����� ������ �߰��ؾ��� 
	IMAGEMANAGER->addImage("�޹��1", "Images/bakcground_day1.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��2", "Images/bakcground_day2.bmp", 1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��3", "Images/bakcground_day3.bmp", 1312, 768, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("���3", "Images/first_p.bmp", 0,0,1312, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���3_c", "Images/first_c.bmp",0,0, 1312, 768, true, RGB(255, 0, 255));

	
	IMAGEMANAGER->addImage("ü��", "Images/life.bmp", 27*2, 35*2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("itemBack", "Images/invenBack.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("food", "Images/food.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("t6", "Images/t6.bmp", 100, 100, true, RGB(255, 0, 255));



	IMAGEMANAGER->addImage("ȭ��ǥ", "Images/arrow.bmp", 40 , 40, true, RGB(255, 0, 255));


	cameraPoint1 = RectMake(1250,0,100,WINSIZE_Y);


	//�ʵ� ������ ���Ͱ� �־ �� ���͸� �޾ƿ��� �������� �ѷ��ִ� �ɷ� �ؾ���
	//�ʵ� ������ �ʱ�ȭ
	//��ġ
	stageItem[0] = RectMake(300, 100,100,100);
	stageItem[1] = RectMake(400, 100, 100, 100);
	stageItem[2] = RectMake(500, 100, 100, 100);
	stageItem[3] = RectMake(600, 100, 100, 100);



	




	//============================================


	//==========================================
	playerS->backName = "���3_c";
	playerS->playerInit();

	if (playerS->nowScene == 2)
	{
		playerS->nowScene = 1;
		playerS->rc = RectMake(WINSIZE_X-90, 600, 60, 60);
	}
	else {
		playerS->rc = RectMake(50, 600, 60, 60);

	}

	
	player2 = playerS;
	

	//==========================================
	for (int i = 0; i < monsterCount; i++)
	{
		m[i] = new monster();

		m[i]->monsterInit();
		m[i]->playerRect = &player2->rc2;

	}
	m[0]->setLocation(600, 500);
	m[1]->setLocation(1000, 400);
	return S_OK;
}

void popolScene::release()
{
}

void popolScene::update()
{
	//�÷��̾�� ������ ���� �Է� -> ���Ϳ��� �浹 ó���� ���
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

	RECT temp5;
	for (int i = 0; i < fieldVec.size(); i++)
	{
		if (IntersectRect(&temp5, &playerS->rc2, &stageItem[i]))
		{
			stageItem[i].left = -100;
			stageItem[i].right = -100;

			player2->invenVec2.push_back(fieldVec.at(i));
		}


	}
	
	

	player2->playerMovement();
	if (player2->rc2.right > WINSIZE_X)
	{
		SCENEMANAGER->changeScene("����2");
	}


	for (int i = 0; i < monsterCount; i++)
	{
		m[i]->monsterMoveMent();
	}
	

	_alpha -= 3.0f;

	if (_alpha <= 0)
	{
		_alpha = 255;
	}
	//CAMERA.x += -player2->CAMERA;
	//IMAGEMANAGER->findImage("���3_c")->setX(CAMERA.x);
	//IMAGEMANAGER->findImage("���3_c")->setY(0+CAMERA.y);
	

	IMAGEMANAGER->findImage("���3")->setX(CAMERA.x);
	//IMAGEMANAGER->findImage("���3")->setY(0+CAMERA.y);

	cout << "���� �÷��̾ ������ �ִ� ������";
	for (int i = 0; i < playerS->invenVec2.size(); i++)
	{
		cout << playerS->invenVec2.at(i);
	}
	cout << endl;

}

void popolScene::render()
{

	IMAGEMANAGER->render("�޹��1", getMemDC());
	IMAGEMANAGER->render("�޹��2", getMemDC());
	IMAGEMANAGER->render("�޹��3", getMemDC());


	//IMAGEMANAGER->render("���3_c", getMemDC(), IMAGEMANAGER->findImage("���3_c")->getX(), IMAGEMANAGER->findImage("���3_c")->getY());

	IMAGEMANAGER->render("���3", getMemDC(), IMAGEMANAGER->findImage("���3")->getX(), IMAGEMANAGER->findImage("���3")->getY());

	for (int i = 0; i < player2->lifeCount; i++)
	{
		IMAGEMANAGER->render("ü��", getMemDC(),30+i*55,50);
	}
	for (int i = 0; i < 5; i++)
	{
		
		IMAGEMANAGER->render("itemBack", getMemDC(), 700 + i * 62, 50);
		IMAGEMANAGER->render("food", getMemDC(), 700+4 + i * 62, 54);
	}


	for (int i = 0; i < fieldVec.size(); i++)
	{
		if (fieldVec.at(i) == "�����" || fieldVec.at(i) == "����")
		{
			IMAGEMANAGER->render("t6", getMemDC(), stageItem[i].left, stageItem[i].top);
		}
	}
	/*

	//RectangleMake(getMemDC(), rc);
	RectangleMake(getMemDC(),playerS->rc2);
	//RectangleMake(getMemDC(), m[0].mRc);

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
			IMAGEMANAGER->frameRender("skel_death", getMemDC(), m[i]->mRc.left, m[i]->mRc.top);
		}else if (m[i]->state == 0)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_idle");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_idle", getMemDC(), m[i]->mRc.left, m[i]->mRc.top);

		}
		else if (m[i]->state == 1)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_walk");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_walk", getMemDC(), m[i]->mRc.left, m[i]->mRc.top);

		}
		else if (m[i]->state == 2)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_attack");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_attack", getMemDC(), m[i]->mRc.left, m[i]->mRc.top);

		}
		else if (m[i]->state == 3)
		{
			m[i]->monsterImg = IMAGEMANAGER->findImage("skel_hit");
			m[i]->monsterImg->setFrameY(m[i]->dy);
			IMAGEMANAGER->frameRender("skel_hit", getMemDC(), m[i]->mRc.left, m[i]->mRc.top);
		}
 
	}
	


	
	//RectangleMake(getMemDC(), foothold[0]);
//	RectangleMake(getMemDC(), foothold[1]);
	//RectangleMake(getMemDC(), foothold[2]);

	//RectangleMake(getMemDC(), m[0].mRc);
	//RectangleMake(getMemDC(), m[1].mRc);

	//RectangleMake(getMemDC(), cameraPoint1);

	IMAGEMANAGER->alphaRender("ȭ��ǥ", getMemDC(), WINSIZE_X - 75, WINSIZE_Y / 2 - 40, _alpha);


	//sprintf(str, "���콺 ��ǥ x : %d , y : %d  m[0]�� ste : %d", _ptMouse.x, _ptMouse.y, m[0]->ste);
	//TextOut(getMemDC(), 10, 10, str, strlen(str));
	
	
}
