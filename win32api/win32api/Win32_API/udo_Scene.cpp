#include "setDefine.h"
#include "udo_Scene.h"



HRESULT udo_Scene::init()
{
	//player정보 초기화
	_player.centerX = WINSIZE_X / 2;
	_player.centerY = WINSIZE_Y / 2;
	_player.rc = RectMakeCenter(_player.centerX, _player.centerY,64,64);
	_player.speed = 5.0f;

	//미사일 정보 초기화
	memset(&_missile, 0, sizeof(_missile));

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		_missile[i].keepGoing = false;
		_missile[i].startX = RND->getFromFloatTo(0, WINSIZE_X);
		_missile[i].startY = RND->getFromFloatTo(0, WINSIZE_Y);

		_missile[i].centerX = _missile[i].startX;
		_missile[i].centerY = _missile[i].startY;

		_missile[i].rc = RectMakeCenter(_missile[i].startX, _missile[i].startY, 30, 30);

		_missile[i].speed = RND->getFromFloatTo(2.0f, 4.0f);

	}

	return S_OK;
}

void udo_Scene::release()
{

}

void udo_Scene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.centerX -= _player.speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.centerX += _player.speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player.centerY -= _player.speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_player.centerY += _player.speed;
	}

	//=============================================

	//플레이어의 좌표 갱신
	_player.rc = RectMakeCenter(_player.centerX, _player.centerY, 64, 64);

	//미사일의 좌표 갱신
	for (int i = 0; i < MISSILE_MAX; i++)
	{
		_missile[i].rc = RectMakeCenter(_missile[i].centerX, _missile[i].centerY, 30, 30);
	}
	

	missileMovement();
}

void udo_Scene::render()
{
	RectangleMake(getMemDC(), _player.rc);

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		RectangleMake(getMemDC(), _missile[i].rc);
	}

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		EllipseMakeCenter(getMemDC(), _player.centerX, _player.centerY, FOLLOW * 2, FOLLOW * 2);
	}

}

void udo_Scene::missileMovement()
{
	for (int i = 0; i < MISSILE_MAX; i++)
	{
		//플레이어와 미사일 간의 거리를 구하기 ( 두 점 사이의 거리 )
		int distance = getDistance(_player.centerX, _player.centerY,
			_missile[i].centerX, _missile[i].centerY);

		//두 개체 간의 거리가 FOLLOW 값보다 크고, keepGoing이 false일 경우
		if (distance > FOLLOW && !_missile[i].keepGoing)
		{
			_missile[i].angle = getAngle(_missile[i].centerX, _missile[i].centerY, _player.centerX, _player.centerY);
		}
		else
		{
			_missile[i].keepGoing = true;
		}

		//유도탄의 이동 처리
		_missile[i].centerX += cosf(_missile[i].angle) * _missile[i].speed;
		_missile[i].centerY += -sinf(_missile[i].angle) * _missile[i].speed;


		//유도탄이 화면 밖을 벗어났을 때 화면 안의 어딘가에서 나타나도록
		if (_missile[i].centerX < -50 || _missile[i].centerX > WINSIZE_X + 50 ||
			_missile[i].centerY < -50 || _missile[i].centerY > WINSIZE_Y +50)
		{
			_missile[i].keepGoing = false;
			_missile[i].startX = RND->getFromFloatTo(0, WINSIZE_X);
			_missile[i].startY = RND->getFromFloatTo(0, WINSIZE_Y);

			_missile[i].centerX = _missile[i].startX;
			_missile[i].centerY = _missile[i].startY;

			_missile[i].rc = RectMakeCenter(_missile[i].startX, _missile[i].startY, 30, 30);

			_missile[i].speed = RND->getFromFloatTo(2.0f, 4.0f);
		}
	}
}

