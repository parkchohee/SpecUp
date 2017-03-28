#pragma once
#include "gameNode.h"
#define STUDENTCOUNT 8
#define SKILLCOUNT 8
#define PLAYCOUNT 0.08f

class cHuman;
class cTeacher;
class cPlayer;

struct stBTNEFFECT
{
	image*	img;
	RECT	rc;
	float	x, y;
	bool	isSee;
	char	key;
};

class cSchoolScene : public gameNode
{
	cPlayer*		m_pPlayer;
	cTeacher*		m_pTeacher;
	cHuman*			m_pStudents[STUDENTCOUNT];
	image*			m_pStartImage;
	image*			m_pEndImage;
	image*			m_pPauseImage;
	image*			m_pPauseBtnImage;

	float			m_nTimeCount;
	float			m_nRandomCount;
	float			m_nPlayCount;
	RECT			m_recBtnBackground;
	RECT			m_recStartPauseLogo;
	RECT			m_recEndLogo;
	RECT			m_recPauseBtn;

	RECT			m_recBtnSkill[SKILLCOUNT];

	int				m_nSkillNum;
	bool			m_bGameStart;
	bool			m_bPause;
	bool			m_bStart;
	bool			m_bTimeOut;

	int				m_nMissCount;
	// 연막
	bool			m_bTeacherSee;			// t : 내가 선생님을 볼수있음
	bool			m_isStayKeyDown;		// 키를 눌렀는지 눌렀으면 누른 스킬 검정색으로 변경
	float			m_fTeacherSeeTime;		// 내가 선생님이 안보이는시간 
	bool			m_bPlayerSee;			// t : 선생님이 나를 볼수있음 안개
	float			m_fPlayerSeeTime;		// 선생님이 나를 못보는시간

	vector<stBTNEFFECT*> m_vUpMiss;

public:
	cSchoolScene();
	~cSchoolScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void CheckState();
	void SetRandomCount();
	void ColorCheck();
	void addUpMiss(float x, float y, char key);
	void moveUpMiss();
};

