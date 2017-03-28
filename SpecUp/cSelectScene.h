#pragma once
#include "gameNode.h"
#define BTNCOUNT 3
class cSelectScene : public gameNode
{
	RECT m_recBtn[BTNCOUNT];

public:
	cSelectScene();
	~cSelectScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

