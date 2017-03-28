#pragma once
#include"gameNode.h"
class Scene2 : public gameNode
{
private:
	RECT player;
	RECT attackrect;
	RECT doorrect;
	float playerX;
	float playerY;
	float GateHp;
	float dmg;

	int count;
	int index;
	bool isattack;
	int fakex;
	int fakey;
	float attackrange;
	bool dooropen;

	image* MainGate;
	image* dmgGate;
	image * attackeffect;
	float attackdmg;
	RECT Wallrect_left;
	RECT Wallrect_right;
	int stage;
	float time;
	float attackspeed;
	int fixWallY;
	image* MainGate2;

	float m_fCreativity; //창의력
	float m_fFitness;    //체력
	float m_fKnowledge;  //지식


	float AttackTime;
	bool gameover;
	image* attacker;
	float indexdelay;
	bool attackmotion;
	image* mover;
	float distance;
	int moverindex;
	int movercount;

public:
	Scene2();
	~Scene2();

	HRESULT init();
	void update();
	void render();
	void attack();
	void KeyInPut();
	void attackUpdate();
	void GateFrameUpdate();
	void DontMove();
	void LoadDeta();
	void playerFrame();
};

