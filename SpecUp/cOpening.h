#pragma once
#include "gameNode.h"
class cOpening : public gameNode
{
	int m_nAlphaCnt;
	int m_nCount;

public:
	cOpening();
	~cOpening();

	HRESULT init();
	void release();
	void update();
	void render();

	void alphaFrame();
};

