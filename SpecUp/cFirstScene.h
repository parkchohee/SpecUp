#pragma once
#include "gameNode.h"

struct MOVE_IMG
{
	RECT rc;
	image* img;
	bool isStop;
	int	 x, y;
	int	 spd;
	int	 count;
	int  alpha;
};

class cFirstScene : public gameNode
{
private:
	MOVE_IMG m_stCtop;
	MOVE_IMG m_stTitle;

	int		 m_nDir;
public:
	cFirstScene();
	~cFirstScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void MoveRect();
	void SaveDatabase();
};
