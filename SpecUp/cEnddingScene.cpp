#include "stdafx.h"
#include "cEnddingScene.h"
#include "cPlayer.h"
#include <iostream>

cEnddingScene::cEnddingScene()
{
}


cEnddingScene::~cEnddingScene()
{
}

HRESULT cEnddingScene::init()
{
	m_pPlayer = new cPlayer;

	m_pPlayer->LoadDatabase();

	return S_OK;
}

void cEnddingScene::release()
{
}

void cEnddingScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("FirstScene");
	}
}

void cEnddingScene::render()
{
	char a[100];
	string _add;
	string _school, _leveling;

	switch (_round)
	{
	case 0:
		_school = "유치원 졸업";
		break;
	case 1:
		_school = "초등학교 졸업";
		break;
	case 2:
		_school = "중학교 졸업";
		break;
	case 3:
		_school = "고등학교 졸업";
		break;
	case 4:
		_school = "대학교 졸업";
	case 5:
		_school = "회사 입사";
		break;
	}
	switch (_level)
	{
	case 1:
		_leveling = "꼴통 ";
		break;
	case 2:
		_leveling = "똥꼬 ";
		break;
	case 3:
		_leveling = "존잘 ";
		break;
	}

	float fAdd = m_pPlayer->getCreativity() + m_pPlayer->getFitness() + m_pPlayer->getKnowledge();
	sprintf_s(a, "%4.0f", fAdd);
	_add = _leveling + _school + " : " + a + "점";

	IMAGEMANAGER->render("졸업장", getMemDC());

	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "도담9");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	
	TextOut(getMemDC(), 110, CENTERY - 50, _add.c_str(), strlen(_add.c_str()));
	if(_round != 5) TextOut(getMemDC(), 150, CENTERY + 20, "졸업을 축하합니다!!", strlen("졸업을 축하합니다!!"));
	else   TextOut(getMemDC(), 150, CENTERY + 20, "입사를 축하합니다!!", strlen("졸업을 축하합니다!!"));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "도담9");
	oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	TextOut(getMemDC(), 190, CENTERY + 210, "2016년 XX월 XX일", strlen("2016년 XX월 XX일"));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}
