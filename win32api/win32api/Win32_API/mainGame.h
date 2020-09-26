#pragma once
#include "gameNode.h"

/* ===================================
				내가 만든 Scene 목록
=================================== */
#include "Scene_alphaRender.h"
#include "Scene_galaga.h"
#include "Scene_loopRender.h"
#include "TestProj.h"
#include "Scene_animation.h"
#include "p_Scene.h"
#include "birdScene.h"
#include "Scene_shop.h"
#include "popolScene.h"
#include "Scene_LoadingScene.h"
#include "Scene_ShootingBullet.h"
#include "udo_Scene.h"
#include "stage2.h"
#include "stage3.h"
class mainGame : public gameNode
{
private:

	int A = 0;
	int loadingIMG=0;
	bool loadingOn = false;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

