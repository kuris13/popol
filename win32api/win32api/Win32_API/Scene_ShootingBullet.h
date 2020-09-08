#pragma once
#include "gameNode.h"


typedef struct
{
	float x,y,startX, startY;
	RECT rc;
	image* img;
}BULLET2;


class Scene_ShootingBullet : public gameNode
{
private:
	vector<BULLET2> _bullet;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	//탄 처리하는 함수
	void BulletMoveMent();

	Scene_ShootingBullet();
	~Scene_ShootingBullet();
};

