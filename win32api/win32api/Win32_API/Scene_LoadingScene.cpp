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
		//�ε��� �Ϸ�� ��� Scene�̵�
		SCENEMANAGER->changeScene("���ķ���");
	}
}

void Scene_LoadingScene::render()
{
	_loading->render();
}

void Scene_LoadingScene::loadingImage()
{
	//������ CPU ó�� �ӵ��� �ſ� ������ ������, �ε��� �ϴ� ô�ϰ� �����
	for (int i = 0; i < 300; i++)
	{
		_loading->loadImage("�׽�Ʈ",1,1);
	}

	//���� �ε�
	_loading->loadImage("�̹���", "Images/t1.bmp", 32, 30, true, RGB(255, 255, 255));
}

void Scene_LoadingScene::loadingSound()
{

}
