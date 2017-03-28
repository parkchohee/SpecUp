#include "stdafx.h"
#include "cSelectScene.h"


cSelectScene::cSelectScene()
{
}


cSelectScene::~cSelectScene()
{
}

HRESULT cSelectScene::init()
{
	
	m_recBtn[0] = RectMake(60, 245, 424, 107);
	m_recBtn[1] = RectMake(60, 424, 424, 107);
	m_recBtn[2] = RectMake(60, 605, 424, 107);

	return S_OK;
}

void cSelectScene::release()
{
}

void cSelectScene::update()
{
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < BTNCOUNT; i++)
		{
			if (PtInRect(&m_recBtn[i], _ptMouse))
			{
				switch (i)
				{
				case 0:
					_level = 3;
					break;
				case 1:
					_level = 2;
					break;
				case 2:
					_level = 1;
					break;
				default:
					break;
				}
				SCENEMANAGER->changeScene("SchoolScene");
			}
		}
	}
}

void cSelectScene::render()
{
	IMAGEMANAGER->findImage("selectMode")->render(getMemDC());
}
