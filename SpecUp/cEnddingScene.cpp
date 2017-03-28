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
		_school = "��ġ�� ����";
		break;
	case 1:
		_school = "�ʵ��б� ����";
		break;
	case 2:
		_school = "���б� ����";
		break;
	case 3:
		_school = "����б� ����";
		break;
	case 4:
		_school = "���б� ����";
	case 5:
		_school = "ȸ�� �Ի�";
		break;
	}
	switch (_level)
	{
	case 1:
		_leveling = "���� ";
		break;
	case 2:
		_leveling = "�˲� ";
		break;
	case 3:
		_leveling = "���� ";
		break;
	}

	float fAdd = m_pPlayer->getCreativity() + m_pPlayer->getFitness() + m_pPlayer->getKnowledge();
	sprintf_s(a, "%4.0f", fAdd);
	_add = _leveling + _school + " : " + a + "��";

	IMAGEMANAGER->render("������", getMemDC());

	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "����9");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	
	TextOut(getMemDC(), 110, CENTERY - 50, _add.c_str(), strlen(_add.c_str()));
	if(_round != 5) TextOut(getMemDC(), 150, CENTERY + 20, "������ �����մϴ�!!", strlen("������ �����մϴ�!!"));
	else   TextOut(getMemDC(), 150, CENTERY + 20, "�Ի縦 �����մϴ�!!", strlen("������ �����մϴ�!!"));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "����9");
	oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	TextOut(getMemDC(), 190, CENTERY + 210, "2016�� XX�� XX��", strlen("2016�� XX�� XX��"));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}
