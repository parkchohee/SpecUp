#pragma once
#include "gameNode.h"
enum e_Icon
{
	FOOD_UP,
	WATCH_UP,
	GLASSES_UP,
	FOOD_DOWN,
	WATCH_DOWN,
	GLASSES_DOWN
};

enum e_Lv
{
	EASY,
	NORMAL,
	HARD
};
class cHuman : public gameNode
{
	image*      m_pHumanImage;
	image*      m_pSkillImage;
	RECT      m_recHuman;
	RECT		m_icon;
	e_Icon      m_eSkill;
	e_Lv      m_eLevel;

	int         m_nFrameCount;
	int         m_nFrameX;
	int         m_nSkillFrameX;
	float      m_fStart_time;
	float      m_fEnd_time;
	float      m_fCurrunt_time;
	float      m_fTicktok_time;
	float      m_fLevel;
	bool      m_Move;
	bool      m_bStart;
public:
	cHuman();
	~cHuman();

	HRESULT init(char* fileName, int x, int y);
	void release();
	void update();
	void render();

	void FrameCount();
	void SetMove();
	void SetSkill();
	void UseSkill();
	int getSkill() { return (int)m_eSkill; }
	RECT GetRect() { return m_icon; }
	bool getStart() { return m_bStart; }
	void SetEnd();
};