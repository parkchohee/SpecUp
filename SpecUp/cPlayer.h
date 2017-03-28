#pragma once
#include "gameNode.h"
enum PLAYER_STATE
{
	IDLE,
	FUN,
	SLEEP
};


class cPlayer : public gameNode
{
	image*		m_pPlayerImage;
	RECT		m_recPlayer;
	PLAYER_STATE	m_eSTATE;

	float		m_fCreativity;
	float		m_fFitness;
	float		m_fKnowledge;

	int			m_nFrameCount;
	int			m_nFrameX;
public:
	cPlayer();
	~cPlayer();

	HRESULT init(int x, int y);
	void release();
	void update();
	void render();

	void upCreativity(float creativity);
	void upFitness(float fitness);
	void upKnowledge(float knowledge);

	// Ãß°¡
	float getCreativity() { return m_fCreativity; }
	float getFitness() { return m_fFitness; }
	float getKnowledge() { return m_fKnowledge; }

	void LoadDatabase();
	void SaveDatabase();

	void FrameCount();
	void SetMotion(int motion);
};

