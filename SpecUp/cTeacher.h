#pragma once
#include "gameNode.h"

enum TEACHER_STATE
{
	TEACHER_DESK_STAND,      // å�󿡼� �Ĵٺ�.
	TEACHER_DESK_SIT,      // �������»���
	TEACHER_STAND,         // ĥ���Ĵٺ�
	TEACHER_SEE            // ��Ź���� �Ĵٺ�
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
	void SetAttribute(); //��ǳ�� �� ����
	void SetLevel(); // ���� �г� ����(0~2)
	int getColor() { return m_nSelAtr; }
};
