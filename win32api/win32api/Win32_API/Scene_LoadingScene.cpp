#include "setDefine.h"
#include "Scene_LoadingScene.h"

HRESULT Scene_LoadingScene::init()
{
	_loading = new loding;
	_loading->init();


	this->loadingImage();
	this->loadingSound();

	return S_OK;

}

void Scene_LoadingScene::release()
{
	SAFE_DELETE(_loading);
}

void Scene_LoadingScene::update()
{
	_loading->update();

	if (_loading->loadingDone())
	{
		//로딩이 완료된 경우 Scene이동
		SCENEMANAGER->changeScene("알파렌더");
	}
}

void Scene_LoadingScene::render()
{
	_loading->render();
}

void Scene_LoadingScene::loadingImage()
{
	//현세대 CPU 처리 속도가 매우 빠르기 때문에, 로딩을 하는 척하게 만들기
	for (int i = 0; i < 300; i++)
	{
		_loading->loadImage("테스트",1,1);
	}

	//실제 로딩
	_loading->loadImage("이미지", "Images/t1.bmp", 32, 30, true, RGB(255, 255, 255));
}

void Scene_LoadingScene::loadingSound()
{

}
