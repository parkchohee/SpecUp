#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

HRESULT cPlayer::init(int x, int y)
{
	m_pPlayerImage = IMAGEMANAGER->findImage("player_idle");
	m_recPlayer = RectMake(x, y, 100, 75);
	m_eSTATE = IDLE;

	m_nFrameCount = 0;
	m_nFrameX = 0;

	LoadDatabase();

	return S_OK;
}

void cPlayer::release()
{
}

void cPlayer::update()
{
	FrameCount();
}

void cPlayer::render()
{
	//Rectangle(getMemDC(), m_recPlayer.left, m_recPlayer.top, m_recPlayer.right, m_recPlayer.bottom);
	IMAGEMANAGER->findImage("desk")->render(getMemDC(), m_recPlayer.left, m_recPlayer.top);
	m_pPlayerImage->frameRender(getMemDC(), m_recPlayer.left + 50 - m_pPlayerImage->getFrameWidth() / 2, m_recPlayer.top, m_nFrameX, _round);
	
	char str[100];
	HFONT myFont = CreateFont(15, 0, 0, 0, 800, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "도담9");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	sprintf_s(str, "창의력   : %4.0f", m_fCreativity);
	TextOut(getMemDC(), 25, 35, str, strlen(str));
	sprintf_s(str, "체력     : %4.0f", m_fFitness);
	TextOut(getMemDC(), 25, 55, str, strlen(str));
	sprintf_s(str, "지식     : %4.0f", m_fKnowledge);
	TextOut(getMemDC(), 25, 75, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
	
}

void cPlayer::upCreativity(float creativity)
{
	m_fCreativity += creativity;
	
	if (m_fCreativity < 0)
		m_fCreativity = 0.0f;

	SaveDatabase();
}

void cPlayer::upFitness(float fitness)
{
	m_fFitness += fitness;

	if (m_fFitness < 0)
		m_fFitness = 0.0f;

	SaveDatabase();
}

void cPlayer::upKnowledge(float knowledge)
{
	m_fKnowledge += knowledge;

	if (m_fKnowledge < 0)
		m_fKnowledge = 0.0f;

	SaveDatabase();
}

void cPlayer::LoadDatabase()
{
	FILE *fp = NULL;
	fopen_s(&fp, "playerData.txt", "r");
	
	fscanf_s(fp, "%f", &m_fCreativity);
	fscanf_s(fp, "%f", &m_fFitness);
	fscanf_s(fp, "%f", &m_fKnowledge);

	fclose(fp);
}

void cPlayer::SaveDatabase()
{
	FILE *fp = NULL;
	fopen_s(&fp, "playerData.txt", "w");
	
	fprintf_s(fp, "%f %f %f", m_fCreativity, m_fFitness, m_fKnowledge);
	
	fclose(fp);
}


void cPlayer::FrameCount()
{
	m_nFrameCount++;
	if (m_nFrameCount % 20 == 0)
	{
		m_nFrameX++;
		if (m_nFrameX > m_pPlayerImage->getMaxFrameX())
			m_nFrameX = 0;
		m_nFrameCount = 0;
	}
}

void cPlayer::SetMotion(int motion)
{
	//motion 0 : IDLE 1 : FUN 2 : SLEEP
	if (m_eSTATE == IDLE)
	{
		if (motion == 1)
		{
			m_eSTATE = FUN;
			m_pPlayerImage = IMAGEMANAGER->findImage("player_fun");
			m_nFrameX = 0;
		}
		else if (motion == 2)
		{
			m_eSTATE = SLEEP;
			m_pPlayerImage = IMAGEMANAGER->findImage("player_sleep");
			m_nFrameX = 0;
		}
	}
	else if (m_eSTATE == FUN)
	{
		if (motion == 0)
		{
			m_eSTATE = IDLE;
			m_pPlayerImage = IMAGEMANAGER->findImage("player_idle");
			m_nFrameX = 0;
		}
		else if (motion == 2)
		{
			m_eSTATE = SLEEP;
			m_pPlayerImage = IMAGEMANAGER->findImage("player_sleep");
			m_nFrameX = 0;
		}
	}
	else if (m_eSTATE == SLEEP)
	{
		if (motion == 0)
		{
			m_eSTATE = IDLE;
			m_pPlayerImage = IMAGEMANAGER->findImage("player_idle");
			m_nFrameX = 0;
		}
		else if (motion == 1)
		{
			m_eSTATE = FUN;
			m_pPlayerImage = IMAGEMANAGER->findImage("player_fun");
			m_nFrameX = 0;
		}
	}
}
