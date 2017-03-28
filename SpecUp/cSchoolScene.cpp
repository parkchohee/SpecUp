#include "stdafx.h"
#include "cSchoolScene.h"
#include "cHuman.h"
#include "cTeacher.h"
#include "cPlayer.h"

cSchoolScene::cSchoolScene()
{
}


cSchoolScene::~cSchoolScene()
{
}

HRESULT cSchoolScene::init()
{
	m_bGameStart = true;
	// 플레이어 생성
	m_pPlayer = new cPlayer;
	m_pPlayer->init(218, 400);

	// 주변학생생성
	for (int i = 0; i < STUDENTCOUNT; i++)
	{
		if (i > 3)
		{
			// 플레이어 자리 넘기고 계산
			m_pStudents[i] = new cHuman;

			if (i % 2 == 0)
				m_pStudents[i]->init("man", 78 + ((i + 1) % 3) * 140, 300 + ((i + 1) / 3) * 100);
			else
				m_pStudents[i]->init("woman", 78 + ((i + 1) % 3) * 140, 300 + ((i + 1) / 3) * 100);
		}
		else
		{
			// 주변 학생 이미지로 초기화.
			m_pStudents[i] = new cHuman;

			if (i % 2 == 0)
				m_pStudents[i]->init("man", 78 + (i % 3) * 140, 300 + (i / 3) * 100);
			else
				m_pStudents[i]->init("woman", 78 + (i % 3) * 140, 300 + (i / 3) * 100);
		}
	}

	// 플레이어 스킬 사용버튼
	m_recBtnBackground = RectMake(0, 600, WINSIZEX, WINSIZEY - 600);
	for (int i = 0; i < SKILLCOUNT; i++)
	{
		m_recBtnSkill[i] = RectMake(0 + i * (WINSIZEX / 3), 600, WINSIZEX / 3, WINSIZEY - 600);
	}

	// 선생님 생성
	m_pTeacher = new cTeacher;
	m_pTeacher->init("teacher", CENTERX - 40, 120);

	m_nTimeCount = 0.f;
	m_nSkillNum = 0;
	m_nMissCount = 0;
	m_nPlayCount = 0.0f;

	m_bTeacherSee = true;
	m_bPlayerSee = true;

	m_pStartImage = IMAGEMANAGER->findImage("startLogo");
	m_pPauseImage = IMAGEMANAGER->findImage("pauseLogo");
	m_pEndImage = IMAGEMANAGER->findImage("timeoutLogo");
	m_pPauseBtnImage = IMAGEMANAGER->findImage("pauseBtn");
	m_recStartPauseLogo = RectMake(70, 340, 400, 100);
	m_recEndLogo = RectMake(20, 320, 500, 100);
	m_recPauseBtn = RectMake(490, 0, 50, 50);
	m_bPause = false;
	m_bStart = false;
	m_bTimeOut = false;
	m_isStayKeyDown = false;

	SetRandomCount();
	m_vUpMiss.clear();

	return S_OK;
}

void cSchoolScene::release()
{
	for (int i = 0; i < STUDENTCOUNT; i++)
	{
		SAFE_DELETE(m_pStudents[i]);
	}

	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pTeacher);
}

void cSchoolScene::update()
{
	if (!m_bGameStart)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			SCENEMANAGER->changeScene("Scene2");
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && !m_bStart)
	{
		m_bStart = true;
		SOUNDMANAGER->play("schoolTheme", BGMVOLUME);
	}

	if (!m_bStart)	return;
	if (!m_bPause)
	{
		m_nRandomCount -= TIMEMANAGER->getElapsedTime();
		if (m_nRandomCount < 0)
		{
			m_pStudents[RND->getInt(STUDENTCOUNT)]->SetMove();
			SetRandomCount();
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			m_nPlayCount += TIMEMANAGER->getElapsedTime();
			m_isStayKeyDown = true;
			if (m_nPlayCount > PLAYCOUNT)
			{
				m_nSkillNum = 1;
				CheckState();
				addUpMiss((m_recBtnSkill[0].left + m_recBtnSkill[0].right) / 2, (m_recBtnSkill[0].bottom + m_recBtnSkill[0].top) / 2, 'A');
			}
			m_pPlayer->SetMotion(1);

			SOUNDMANAGER->stop("study");
			SOUNDMANAGER->stop("sleep");
			SOUNDMANAGER->play("loud", 10.f);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			m_nPlayCount += TIMEMANAGER->getElapsedTime();
			m_isStayKeyDown = true;
			if (m_nPlayCount > PLAYCOUNT)
			{
				m_nSkillNum = 2;
				CheckState();
				addUpMiss((m_recBtnSkill[1].left + m_recBtnSkill[1].right) / 2, (m_recBtnSkill[1].bottom + m_recBtnSkill[1].top) / 2, 'S');
			}
			m_pPlayer->SetMotion(2);

			SOUNDMANAGER->stop("study");
			SOUNDMANAGER->stop("loud");
			SOUNDMANAGER->play("sleep", 10.f);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			m_nPlayCount += TIMEMANAGER->getElapsedTime();
			m_isStayKeyDown = true;
			if (m_nPlayCount > PLAYCOUNT)
			{
				m_nSkillNum = 3;
				CheckState();
				addUpMiss((m_recBtnSkill[2].left + m_recBtnSkill[2].right) / 2, (m_recBtnSkill[2].bottom + m_recBtnSkill[2].top) / 2, 'D');
			}
			m_pPlayer->SetMotion(0);

			SOUNDMANAGER->stop("loud");
			SOUNDMANAGER->stop("sleep");
			SOUNDMANAGER->play("study", 10.f);
		}
		else
		{
			m_isStayKeyDown = false;
			m_nPlayCount = 0.0f;
		}

		m_pPlayer->update();

		for (int i = 0; i < STUDENTCOUNT; i++)
		{
			m_pStudents[i]->update();
		}

		m_pTeacher->update();

		m_nTimeCount += TIMEMANAGER->getElapsedTime();
		if (m_nTimeCount - 60.f > 0)
			m_bGameStart = false;

		if (m_fTeacherSeeTime > 0)
			m_fTeacherSeeTime -= TIMEMANAGER->getElapsedTime();
		if (m_fTeacherSeeTime < 0.0001)
		{
			m_fTeacherSeeTime = 0.f;
			m_bTeacherSee = true;
		}

		if (m_fPlayerSeeTime > 0)
			m_fPlayerSeeTime -= TIMEMANAGER->getElapsedTime();
		if (m_fPlayerSeeTime < 0.0001)
		{
			m_fPlayerSeeTime = 0.f;
			m_bPlayerSee = true;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&m_recPauseBtn, _ptMouse))
		{
			m_bPause = !m_bPause;
			SOUNDMANAGER->stop("loud");
			SOUNDMANAGER->stop("sleep");
			SOUNDMANAGER->stop("study");
			if (!m_bPause) SOUNDMANAGER->resume("schoolTheme");
			else		   SOUNDMANAGER->pause("schoolTheme");
		}
		// 학생들을 클릭했는지
		for (int i = 0; i < STUDENTCOUNT; i++)
		{
			if (PtInRect(&m_pStudents[i]->GetRect(), _ptMouse))
			{
				if (m_pStudents[i]->getStart())
				{
					switch (m_pStudents[i]->getSkill() % 6)
					{
					case 0:
						m_pPlayer->upFitness(10);
						break;
					case 1:
						m_nTimeCount -= 3.f;
						break;
					case 2:
						m_bTeacherSee = false;
						m_fTeacherSeeTime = 3.f;
						break;
					case 3:
						m_pPlayer->upFitness(-10);
						break;
					case 4:
						m_nTimeCount += 3.f;
						break;
					case 5:
						m_bPlayerSee = false;
						m_fPlayerSeeTime = 3.f;
						break;
					default:
						break;
					}
					m_pStudents[i]->SetEnd();
				}
			}
		}
	}
	if (!m_bStart)	m_recStartPauseLogo = RectMake(70, 340, 400, 100);
	else if (m_bPause)	m_recStartPauseLogo = RectMake(70, 340, 400, 100);
	else
		m_recStartPauseLogo = RectMake(0, 0, 0, 0);

	if (!m_bGameStart)
	{
		m_recEndLogo = RectMake(20, 320, 500, 100);
		SOUNDMANAGER->stop("schoolTheme");
	}
	else
		m_recEndLogo = RectMake(0, 0, 0, 0);

	if (!m_bPause)  m_pPauseBtnImage = IMAGEMANAGER->findImage("pauseBtn");
	else			   m_pPauseBtnImage = IMAGEMANAGER->findImage("restartbtn");

	moveUpMiss();
}

void cSchoolScene::render()
{
	// 백그라운드
	IMAGEMANAGER->findImage("schoolBackground")->render(getMemDC());

	IMAGEMANAGER->findImage("whiteboard")->render(getMemDC(), 10, 10);
	// 선생님
	m_pTeacher->render();
	IMAGEMANAGER->findImage("teacherDesk")->render(getMemDC(), 77, 126);
	IMAGEMANAGER->findImage("teacherDesk2")->render(getMemDC(), 240, 180);

	// 플레이어			 
	m_pPlayer->render();

	if (!m_bTeacherSee)
		IMAGEMANAGER->findImage("sky2")->render(getMemDC(), 40, 95);

	if (!m_bPlayerSee)
		IMAGEMANAGER->findImage("sky1")->render(getMemDC(), 218, 400);

	// 학생
	for (int i = 0; i < STUDENTCOUNT; i++)
	{
		m_pStudents[i]->render();
	}

	char timeStr[100];
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "digital-7");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	sprintf_s(timeStr, "%.0f", 60.f - m_nTimeCount);
	TextOut(getMemDC(), CENTERX - 15, 65, timeStr, strlen(timeStr));
	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);

	if (!m_bStart)
		m_pStartImage->render(getMemDC(), m_recStartPauseLogo.left, m_recStartPauseLogo.top);
	if (m_bPause)
		m_pPauseImage->render(getMemDC(), m_recStartPauseLogo.left, m_recStartPauseLogo.top);
	if (!m_bGameStart)
		m_pEndImage->render(getMemDC(), m_recEndLogo.left, m_recEndLogo.top);

	m_pPauseBtnImage->render(getMemDC(), m_recPauseBtn.left, m_recPauseBtn.top);

	IMAGEMANAGER->findImage("board2")->alphaRender(getMemDC(), 0, m_recBtnSkill[0].top, 150);
	IMAGEMANAGER->findImage("board")->render(getMemDC(), 0, m_recBtnSkill[0].top);
	IMAGEMANAGER->findImage("btnPlay")->render(getMemDC(), m_recBtnSkill[0].left + 15, m_recBtnSkill[0].top + 15);
	IMAGEMANAGER->findImage("btnSleep")->render(getMemDC(), m_recBtnSkill[1].left + 15, m_recBtnSkill[1].top + 15);
	IMAGEMANAGER->findImage("btnStudy")->render(getMemDC(), m_recBtnSkill[2].left + 15, m_recBtnSkill[2].top + 15);

	// 플레이어 버튼
	if (m_nSkillNum == 1 && m_isStayKeyDown) IMAGEMANAGER->findImage("pressPlay")->render(getMemDC(), m_recBtnSkill[0].left + 15, m_recBtnSkill[0].top + 15);
	else if (m_nSkillNum == 2 && m_isStayKeyDown) IMAGEMANAGER->findImage("pressSleep")->render(getMemDC(), m_recBtnSkill[1].left + 15, m_recBtnSkill[1].top + 15);
	else if (m_nSkillNum == 3 && m_isStayKeyDown)  IMAGEMANAGER->findImage("pressStudy")->render(getMemDC(), m_recBtnSkill[2].left + 15, m_recBtnSkill[2].top + 15);

	//up, miss 이펙트 렌더
	for (int i = 0; i < m_vUpMiss.size(); i++)
	{
		if (m_bPlayerSee)
		{
			if (m_vUpMiss[i]->isSee)
				m_vUpMiss[i]->img->render(getMemDC(), m_vUpMiss[i]->rc.left, m_vUpMiss[i]->rc.top, 0, 0, 60, 20);
			else
				m_vUpMiss[i]->img->render(getMemDC(), m_vUpMiss[i]->rc.left, m_vUpMiss[i]->rc.top, 0, 20, 60, 20);
		}
		else
		{
			m_vUpMiss[i]->img->render(getMemDC(), m_vUpMiss[i]->rc.left, m_vUpMiss[i]->rc.top, 0, 0, 60, 20);
		}
	}
}

void cSchoolScene::CheckState()
{
	// 선생님이 나를 못봄.. 선글라스 스킬 사용
	if (!m_bPlayerSee)
	{
		if (m_nSkillNum == 1)
		{
			m_pPlayer->upCreativity(0.1);

		}
		else if (m_nSkillNum == 2)
		{
			m_pPlayer->upFitness(0.1);

		}
		else if (m_nSkillNum == 3)
		{
			m_pPlayer->upKnowledge(0.1);

		}
	}
	else
	{
		// 선생님 상태가 앞을본다. 
		// 공부하기ㅡㄹ아닌 다른걸 누르면  감소
		switch (m_pTeacher->GetState())
		{
		case 0:
		case 3://0 , 3 학생 바라봄
			if (m_nSkillNum == 3)
			{
				m_pPlayer->upKnowledge(0.1);
			}
			else
			{
				ColorCheck();
			}
			break;
		case 1://잠자기 선생님의 위치 책상
			if (m_nSkillNum == 2)
				m_pPlayer->upFitness(0.1);
			else
			{
				ColorCheck();
			}
			break;
		case 2://장난치기 선생님의 위치 칠판
			if (m_nSkillNum == 1)
				m_pPlayer->upCreativity(0.1);
			else
			{
				ColorCheck();
			}
			break;
		default:
			break;
		}
	}
}

void cSchoolScene::SetRandomCount()
{
	m_nRandomCount = RND->getFromFloatTo(1.0f, 5.0f);
}

void cSchoolScene::ColorCheck()
{
	m_nMissCount++;
	int a = 1;
	if (m_nMissCount == 3)
	{
		a = 5;
		m_nMissCount = 0;
	}

	switch (m_pTeacher->getColor())
	{
	case 0:
		if (m_nSkillNum == 1)
		{
			m_pPlayer->upCreativity(-0.1 * a);

		}
		else if (m_nSkillNum == 2)
		{
			m_pPlayer->upFitness(-0.1 * a);

		}
		else if (m_nSkillNum == 3)
		{
			m_pPlayer->upKnowledge(-0.1 * a);

		}
		break;
	case 1:
		m_pPlayer->upKnowledge(-0.1 * a);
		break;
	case 2:
		m_pPlayer->upFitness(-0.1 * a);
		break;
	case 3:
		m_pPlayer->upCreativity(-0.1 * a);
		break;
	default:
		break;
	}
	m_pTeacher->SetLevel();
}
//up miss 벡터에 넣어주기
void cSchoolScene::addUpMiss(float x, float y, char key)
{
	stBTNEFFECT* addUm;
	addUm = new stBTNEFFECT;
	addUm->img = IMAGEMANAGER->findImage("upMiss");
	addUm->x = 450 - addUm->img->getWidth() / 2;
	addUm->y = 150 - addUm->img->getHeight() / 2;
	addUm->rc = RectMake(addUm->x, addUm->y, 180, 60);

	switch (m_pTeacher->GetState())
	{
	case 0:
	case 3://0 , 3 학생 바라봄
		if (key == 'D') addUm->isSee = true;
		else  addUm->isSee = false;
		break;
	case 1://잠자기 선생님의 위치 책상
		if (key == 'S') addUm->isSee = true;
		else  addUm->isSee = false;
		break;
	case 2://장난치기 선생님의 위치 칠판
		if (key == 'A') addUm->isSee = true;
		else  addUm->isSee = false;
		break;
	default:
		break;
	}

	addUm->key = key;

	m_vUpMiss.push_back(addUm);
}

void cSchoolScene::moveUpMiss()
{
	for (int i = 0; i < m_vUpMiss.size(); i++)
	{
		m_vUpMiss[i]->rc.top -= 5.0f;
	}

	for (int i = 0; i < m_vUpMiss.size(); i++)
	{
		if (m_vUpMiss[i]->rc.top < 70) m_vUpMiss.erase(m_vUpMiss.begin() + i);
	}
}
