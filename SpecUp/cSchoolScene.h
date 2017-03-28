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
	// ����
	bool			m_bTeacherSee;			// t : ���� �������� ��������
	bool			m_isStayKeyDown;		// Ű�� �������� �������� ���� ��ų ���������� ����
	float			m_fTeacherSeeTime;		// ���� �������� �Ⱥ��̴½ð� 
	bool			m_bPlayerSee;			// t : �������� ���� �������� �Ȱ�
	float			m_fPlayerSeeTime;		// �������� ���� �����½ð�

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

