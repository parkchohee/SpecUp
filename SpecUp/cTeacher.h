#pragma once
#include "gameNode.h"

enum TEACHER_STATE
{
	TEACHER_DESK_STAND,      // 책상에서 쳐다봄.
	TEACHER_DESK_SIT,      // 업무보는상태
	TEACHER_STAND,         // 칠판쳐다봄
	TEACHER_SEE            // 교탁에서 쳐다봄
};

class cTeacher : public gameNode
{
	image*         m_pTeacherImage;
	image*         m_pExcImage;
	image*         m_pImotionImage;
	image*         m_pSBubble;
	RECT         m_recTeacher;
	RECT         m_recImoticon;
	RECT         m_recSBubble;

	int            m_nFrameCount;
	int            m_nFrameX;
	int            m_nX;
	int            m_nY;
	int            m_nLevel;
	int            m_nSelAtr;


	float         m_fRandomCount;
	TEACHER_STATE   m_sState;
	bool          m_Show;
	bool         m_MaxLv;
public:
	cTeacher();
	~cTeacher();

	HRESULT init(char* fileName, int x, int y);
	void release();
	void update();
	void render();

	void FrameCount();
	void SetState();
	int GetState();
	void SetRandomCount();
	void SetAttribute(); //말풍선 색 설정
	void SetLevel(); // 현재 분노 레벨(0~2)
	int getColor() { return m_nSelAtr; }
};
