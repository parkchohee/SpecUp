#pragma once
#include "gameNode.h"

class cTutorialScene : public gameNode
{
	int n;
public:
	cTutorialScene();
	~cTutorialScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

