#include "setDefine.h"
#include "Scene_ShootingBullet.h"



HRESULT Scene_ShootingBullet::init()
{
	return S_OK;
}

void Scene_ShootingBullet::release()
{
}

void Scene_ShootingBullet::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//źȯ ���� �ʱ�ȭ
		BULLET2 b;
		b.startX = b.x = WINSIZE_X/2;
		b.startY = b.y = WINSIZE_Y / 2;
		b.rc = RectMake(b.startX, b.startY,64,64);

		b.img = IMAGEMANAGER->addImage("ź", "Images/t3.bmp", 64, 64,true,RGB(255,0,255));

		//źȯ�� vector ��ü�� ����
		_bullet.push_back(b);
	}

	//źȯ �߻� ��ǥ ó��
	BulletMoveMent();

}

void Scene_ShootingBullet::render()
{
	//���� �ش� Scene�� �����ϴ� źȯ�� ���� ǥ��
	char strSize[128];
	sprintf(strSize, "VectSize : %d", _bullet.size());
	TextOut(getMemDC(), 10, 20, strSize, strlen(strSize));

	//źȯ ����
	for (int i = 0; i < _bullet.size(); i++)
	{
		//Ű���带 ���� ȭ�鿡 ���
		IMAGEMANAGER->render("ź", getMemDC(), _bullet[i].rc.left, _bullet[i].rc.top);
	}

}

void Scene_ShootingBullet::BulletMoveMent()
{
	for (int i = 0; i < _bullet.size(); i++)
	{
		//��ǥ�̵�
		_bullet[i].y -= 5;
		_bullet[i].rc = RectMake(_bullet[i].x, _bullet[i].y, 64, 64);

		//ȭ�� ���� ����ҷ��� �� ��
		if (_bullet[i].y < 0)
		{
			//���Ϳ��� �ش� ��Ҹ� ����
			_bullet.erase(_bullet.begin() + i);
		}
	}
}

Scene_ShootingBullet::Scene_ShootingBullet()
{
}


Scene_ShootingBullet::~Scene_ShootingBullet()
{
}
