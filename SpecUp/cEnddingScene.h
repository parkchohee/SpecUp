#pragma once
#include "gameNode.h"

class cPlayer;

class cEnddingScene : public gameNode
{
private:
	cPlayer*		m_pPlayer;

public:
	cEnddingScene();
	~cEnddingScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

