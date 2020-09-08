#pragma once
#include "gameNode.h"
#include "loding.h"
class Scene_LoadingScene : public gameNode
{
private:
	
	loding* _loading;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void loadingImage();
	void loadingSound();


};

