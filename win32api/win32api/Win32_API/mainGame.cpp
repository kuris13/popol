#include "setDefine.h"
#include "mainGame.h"


HRESULT mainGame::init()
{
	gameNode::init(TRUE);

	//01. ���ĺ���
	SCENEMANAGER->addScene("���ķ���", new Scene_alphaRender);

	//02. ������
	SCENEMANAGER->addScene("������",new Scene_galaga);
	
	//03. ���� ����
	SCENEMANAGER->addScene("��������",new Scene_loopRender );

	//04
	SCENEMANAGER->addScene("�ִϸ��̼�",new Scene_animation );
	
	//05
	SCENEMANAGER->addScene("�ȼ��浹",new p_Scene );

	//�׽�ƮScene
	SCENEMANAGER->addScene("�׽�Ʈ",new TestProj);

	//shop
	SCENEMANAGER->addScene("����", new Scene_shop);

	//popol
	SCENEMANAGER->addScene("����", new popolScene);

	SCENEMANAGER->addScene("�ε�", new Scene_LoadingScene);

	SCENEMANAGER->addScene("����", new Scene_ShootingBullet);

	SCENEMANAGER->addScene("ȣ��", new udo_Scene);

	//������ Scene�� ����
	SCENEMANAGER->changeScene("���ķ���");

	SCENEMANAGER->addScene("����2", new stage2);

	playerS->playerInit();




	//====================================
	//����� ���带 �߰�
	SOUNDMANAGER->addSound("���", "BGM.mp3",true,true);

	//���� ���
	//SOUNDMANAGER->play("���", 0.5f);



	return S_OK;
}

void mainGame::release()
{
	gameNode::release();


}

void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();

	//���� Ű�е� �Է¿� ���� Scene ��ȯ
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0))
		SCENEMANAGER->changeScene("���ķ���");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
		SCENEMANAGER->changeScene("������");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
		SCENEMANAGER->changeScene("��������");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
		SCENEMANAGER->changeScene("�ִϸ��̼�");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		SCENEMANAGER->changeScene("�ȼ��浹");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		SCENEMANAGER->changeScene("�ȼ��浹");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
		SCENEMANAGER->changeScene("����");

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		SCENEMANAGER->changeScene("����");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
		SCENEMANAGER->changeScene("�ε�");

	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
		SCENEMANAGER->changeScene("����");

	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		SCENEMANAGER->changeScene("ȣ��");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("����2");
	}

}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	//render
	SCENEMANAGER->render();

	this->getBackBuffer()->render(getHDC());
}
