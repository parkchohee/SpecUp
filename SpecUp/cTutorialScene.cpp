#include "stdafx.h"
#include "cTutorialScene.h"


cTutorialScene::cTutorialScene()
{
}


cTutorialScene::~cTutorialScene()
{
}

HRESULT cTutorialScene::init()
{
	n = 1;
	return S_OK;
}

void cTutorialScene::release()
{
}

void cTutorialScene::update()
{
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
	{
		n++;
		if (n > 15)
			SCENEMANAGER->changeScene("SelectScene");
	}
	/*if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{

	}*/
}

void cTutorialScene::render()
{
	TextOut(getMemDC(), 100, 100, "여기는 튜토리얼", strlen("여기는 튜토리얼"));
	char str[100];
	sprintf_s(str, "tuto%d", n);
	IMAGEMANAGER->findImage(str)->render(getMemDC());
}
