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
		//탄환 정보 초기화
		BULLET2 b;
		b.startX = b.x = WINSIZE_X/2;
		b.startY = b.y = WINSIZE_Y / 2;
		b.rc = RectMake(b.startX, b.startY,64,64);

		b.img = IMAGEMANAGER->addImage("탄", "Images/t3.bmp", 64, 64,true,RGB(255,0,255));

		//탄환을 vector 객체에 삽입
		_bullet.push_back(b);
	}

	//탄환 발사 좌표 처리
	BulletMoveMent();

}

void Scene_ShootingBullet::render()
{
	//현재 해당 Scene에 존재하는 탄환의 수량 표시
	char strSize[128];
	sprintf(strSize, "VectSize : %d", _bullet.size());
	TextOut(getMemDC(), 10, 20, strSize, strlen(strSize));

	//탄환 묘사
	for (int i = 0; i < _bullet.size(); i++)
	{
		//키워드를 통해 화면에 출력
		IMAGEMANAGER->render("탄", getMemDC(), _bullet[i].rc.left, _bullet[i].rc.top);
	}

}

void Scene_ShootingBullet::BulletMoveMent()
{
	for (int i = 0; i < _bullet.size(); i++)
	{
		//좌표이동
		_bullet[i].y -= 5;
		_bullet[i].rc = RectMake(_bullet[i].x, _bullet[i].y, 64, 64);

		//화면 위를 통과할려고 할 때
		if (_bullet[i].y < 0)
		{
			//벡터에서 해당 요소를 삭제
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
