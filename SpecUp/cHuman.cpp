#include "stdafx.h"
#include "cHuman.h"

cHuman::cHuman()
{
}


cHuman::~cHuman()
{
}

HRESULT cHuman::init(char* fileName, int x, int y)
{
	m_pHumanImage = IMAGEMANAGER->findImage(fileName);
	m_pSkillImage = NULL;
	m_recHuman = RectMake(x, y, 100, 75);

	m_nFrameCount = 0;
	m_nFrameX = 0;
	m_nSkillFrameX = 0;
	m_Move = false;
	m_bStart = false;
	m_fStart_time = 0.0f;
	m_fTicktok_time = 0.0f;
	m_fLevel = 0.0f;
	m_eSkill = FOOD_DOWN;
	m_eLevel = EASY;
	m_fCurrunt_time = 0.0f;

	if (m_eLevel == EASY)
	{
		m_fEnd_time = RND->getFromFloatTo(1.5f, 2.5f);
		m_fLevel = 0.3f;
	}
	if (m_eLevel == NORMAL)
	{
		m_fEnd_time = RND->getFromFloatTo(1.0f, 1.5f);
		m_fLevel = 0.2f;
	}
	if (m_eLevel == HARD)
	{
		m_fEnd_time = RND->getFromFloatTo(0.5f, 1.0f);
		m_fLevel = 0.1f;
	}


	m_icon = RectMake(0, 0, 0, 0);
	return S_OK;
}

void cHuman::release()
{
}

void cHuman::update()
{

	if (m_Move)
	{
		m_fStart_time += TIMEMANAGER->getElapsedTime();
	}
	if ((!m_bStart) && m_fStart_time > 0.3f)
	{
		m_bStart = true;
		SetSkill();
		m_fStart_time = 0.0f;
	}
	UseSkill();
	FrameCount();
}

void cHuman::render()
{
	//Rectangle(getMemDC(), m_recHuman.left, m_recHuman.top, m_recHuman.right, m_recHuman.bottom);
	IMAGEMANAGER->findImage("desk")->render(getMemDC(), m_recHuman.left, m_recHuman.top);
	m_pHumanImage->frameRender(getMemDC(), m_recHuman.left + 50 - m_pHumanImage->getFrameWidth() / 2, m_recHuman.top, m_nFrameX, _round);
	if (m_bStart)
	{
		m_icon = RectMake(m_recHuman.left + 70 - m_pHumanImage->getFrameWidth() / 2, m_recHuman.top - 50, 100, 100);
		m_pSkillImage->frameRender(getMemDC(), m_recHuman.left + 70 - m_pHumanImage->getFrameWidth() / 2, m_recHuman.top - 50, m_nSkillFrameX, 0);

	}
	else
	{
		m_icon = RectMake(0,0,0,0);
		
	}
}

void cHuman::FrameCount()
{
	m_nFrameCount++;
	if (!m_Move)
	{
		if (m_nFrameCount % 20 == 0)
		{
			m_nFrameX++;
			if (m_nFrameX > 1)
				m_nFrameX = 0;
			m_nFrameCount = 0;
		}
	}
	else
	{
		m_nFrameX = 2;
		m_nFrameCount = 0;
	}
}

void cHuman::SetMove()
{
	m_Move = true;
}

void cHuman::SetSkill()
{
	m_fCurrunt_time = 0.0f;
	int rndNum = RND->getInt(3);
	switch (rndNum)
	{
	case 0:
		m_pSkillImage = IMAGEMANAGER->findImage("icon_f");
		m_eSkill = FOOD_DOWN;
		break;
	case 1:
		m_pSkillImage = IMAGEMANAGER->findImage("icon_g");
		m_eSkill = GLASSES_DOWN;
		break;
	case 2:
		m_pSkillImage = IMAGEMANAGER->findImage("icon_w");
		m_eSkill = WATCH_DOWN;
		break;
	}
}

void cHuman::UseSkill()
{
	if (m_bStart)
	{
		m_fTicktok_time += TIMEMANAGER->getElapsedTime();
		m_fCurrunt_time += TIMEMANAGER->getElapsedTime();
		if (m_fTicktok_time > m_fLevel)
		{
			m_nSkillFrameX++;
			if (m_nSkillFrameX > 1)
			{
				m_nSkillFrameX = 0;
			}
			m_eSkill = (e_Icon)(((int)m_eSkill + 3) % 6);
			m_fTicktok_time = 0.0f;
		}

		if (m_fCurrunt_time > m_fEnd_time)
		{
			m_pSkillImage = NULL;
			m_bStart = false;
			m_Move = false;
			m_fCurrunt_time = 0.0f;
			m_fTicktok_time = 0.0f;
			m_fStart_time = 0.0f;
		}

	}

}

void cHuman::SetEnd()
{
	m_pSkillImage = NULL;
	m_bStart = false;
	m_Move = false;
	m_fCurrunt_time = 0.0f;
	m_fTicktok_time = 0.0f;
	m_fStart_time = 0.0f;
}
