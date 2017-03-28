#include "stdafx.h"
#include "cTeacher.h"


cTeacher::cTeacher()
{
}


cTeacher::~cTeacher()
{
}

HRESULT cTeacher::init(char* fileName, int x, int y)
{
	m_nX = x;
	m_nY = y;

	m_pTeacherImage = IMAGEMANAGER->findImage(fileName);
	m_pExcImage = IMAGEMANAGER->findImage("icon_eMark");
	m_pImotionImage = IMAGEMANAGER->findImage("iMoticon");
	m_pSBubble = IMAGEMANAGER->findImage("sBubble");
	m_recTeacher = RectMake(x, y, 100, 75);
	m_recImoticon = RectMake(0, 0, 0, 0);
	m_recSBubble = RectMake(x - 30, y - 30, 60, 60);

	m_nFrameCount = 0;
	m_nFrameX = 2;
	m_sState = TEACHER_SEE;
	m_Show = false;
	m_nLevel = 0;
	m_nSelAtr = 0;
	m_MaxLv = false;
	SetRandomCount();

	return S_OK;
}

void cTeacher::release()
{
}

void cTeacher::update()
{
	m_recSBubble = RectMake(m_recTeacher.left - 30, m_recTeacher.top - 30, 60, 60);
	if (m_fRandomCount > 0)
	{
		if (m_fRandomCount < 0.3f)
		{
			m_recImoticon = RectMake(m_recTeacher.left + 30, m_recTeacher.top - 30, 30, 30);
			m_Show = true;
		}
		else
		{
			m_recImoticon = RectMake(0, 0, 0, 0);
			m_Show = false;
		}
		m_fRandomCount -= TIMEMANAGER->getElapsedTime();
	}
	else
	{
		SetState();
	}

	if (m_MaxLv && m_nSelAtr == 0)
	{
		SetAttribute();
	}


	/*if (KEYMANAGER->isOnceKeyDown('W'))
	{
	SetLevel();
	}*/
}

void cTeacher::render()
{
	m_pTeacherImage->frameRender(getMemDC(), m_recTeacher.left + 25, m_recTeacher.top, m_nFrameX, _round);
	if (m_Show)
		m_pExcImage->render(getMemDC(), m_recImoticon.left + 25, m_recImoticon.top);
	m_pSBubble->frameRender(getMemDC(), m_recSBubble.left + 15, m_recSBubble.top, m_nSelAtr, 0);
	m_pImotionImage->frameRender(getMemDC(), m_recSBubble.left + 15, m_recSBubble.top - 10, m_nLevel, 0);
}

void cTeacher::FrameCount()
{
	m_nFrameCount++;
	if (m_nFrameCount % 10 == 0)
	{
		m_nFrameX++;
		if (m_nFrameX > m_pTeacherImage->getMaxFrameX())
		{
			m_nFrameX = 0;
			SetRandomCount();
		}
		m_nFrameCount = 0;
	}
}

void cTeacher::SetState()
{
	m_sState = (TEACHER_STATE)RND->getInt(6);

	switch (m_sState)
	{
	case 0:
		m_recTeacher = RectMake(m_nX - 180, m_nY - 10, 100, 75);
		m_nFrameX = 0;
		break;
	case 1:
	case 4:
		m_sState = (TEACHER_STATE)1;
		m_recTeacher = RectMake(m_nX - 180, m_nY + 20, 100, 75);
		m_nFrameX = 0;
		break;
	case 2:
	case 5:
		m_sState = (TEACHER_STATE)2;
		m_recTeacher = RectMake(m_nX, m_nY, 100, 75);
		m_nFrameX = 1;
		break;
	case 3:
		m_recTeacher = RectMake(m_nX, m_nY, 100, 75);
		m_nFrameX = 2;
		break;
	default:
		break;
	}

	SetRandomCount();
}

int cTeacher::GetState()
{
	return (int)m_sState;
}

void cTeacher::SetRandomCount()
{
	// 레벨에따라 시간을 줄인다
	switch (_level)
	{
	case 1:
		m_fRandomCount = (RND->getFromFloatTo(1.5f, 2.5f)) - (float)(_round * 0.1f);
		break;
	case 2:
		m_fRandomCount = (RND->getFromFloatTo(1.0f, 2.0f)) - (float)(_round * 0.1f);
		break;
	case 3:
		m_fRandomCount = RND->getFromFloatTo(0.5f, 1.0f) - (float)(_round * 0.1f);
		break;
	default:
		m_fRandomCount = RND->getFromFloatTo(1.5f, 2.5f) - (float)(_round * 0.1f);
		break;
	}
}

void cTeacher::SetAttribute()
{
	m_nSelAtr = RND->getFromIntTo(1, 3);
}

void cTeacher::SetLevel()
{
	m_nLevel++;
	if (m_nLevel > 2)
	{
		m_nLevel = 0;
		m_MaxLv = false;
		m_nSelAtr = 0;
	}
	if (m_nLevel == 2) m_MaxLv = true;
}