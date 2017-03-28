#include "stdafx.h"
#include "cOpening.h"


cOpening::cOpening()
{
}


cOpening::~cOpening()
{
}

HRESULT cOpening::init()
{
	m_nAlphaCnt = -255;
	m_nCount = 0;
	return S_OK;
}

void cOpening::release()
{
}

void cOpening::update()
{
	alphaFrame();
}

void cOpening::render()
{
	if (m_nAlphaCnt < 0)
	{
		IMAGEMANAGER->findImage("world_alpha")->alphaRender(getMemDC(), 0, 0, 255 + m_nAlphaCnt);
	}
	else
	{
		SCENEMANAGER->changeScene("TutorialScene");
	}
}

void cOpening::alphaFrame()
{
	if (m_nAlphaCnt < 0)
	{
		m_nCount++;
		if (m_nCount % 3 == 0)
		{
			m_nAlphaCnt += 5;
			m_nCount = 0;
		}
	}
}
