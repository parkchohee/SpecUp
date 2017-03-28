#include "stdafx.h"
#include "Scene2.h"


Scene2::Scene2()
{
}


Scene2::~Scene2()
{
}
HRESULT Scene2::init()
{
	playerX = CENTERX - 25;
	if (_round >= 2)distance = 10.f;
	else distance = 200.f;
	playerY = CENTERY - 75 + distance;
	player = RectMake(playerX, playerY, 50, 50);
	GateHp = 100.f;
	dmg = 2.f;
	count = 0;
	index = 0;

	//attackeffect
	attackeffect = IMAGEMANAGER->addFrameImage("attackeffect", "image/Scene2/attackeffect.bmp", 450, 98, 6, 1, true, RGB(255, 0, 255));
	isattack = false;
	doorrect = RectMake(210, 230, 140, 70);
	fakex = 0;
	fakey = 0;

	attackrange = 20;

	//MainGate = IMAGEMANAGER->addFrameImage("MainGate", "image/Scene2/MainGate.bmp", 130, 400, 1, 4, true, RGB(255, 0, 255));
	//dmgGate = IMAGEMANAGER->addFrameImage("dmgGate", "image/Scene2/dmgGate.bmp", 130, 400, 1, 4, true, RGB(255, 0, 255));
	MainGate2 = IMAGEMANAGER->addFrameImage("MainGate2", "image/Scene2/MainGate2.bmp", 240, 100, 2, 1, true, RGB(254, 0, 254));



	Wallrect_left = RectMake(0, 180, 205, 120);
	Wallrect_right = RectMake(340, 180, 205, 120);
	dooropen = false;

	stage = 0;
	fixWallY = 0;
	AttackTime = 0.f;
	gameover = false;
	attackmotion = false;
	indexdelay = 0.f;

	mover = IMAGEMANAGER->addFrameImage("mover", "image/Scene2/mover.bmp", 200, 450, 4, 5, true, RGB(255, 0, 255));
	mover->setFrameX(0);
	mover->setFrameY(_round);

	attacker = IMAGEMANAGER->addFrameImage("attacker", "image/Scene2/attacker.bmp", 100, 450, 2, 5, true, RGB(255, 0, 255));
	attacker->setFrameX(0);
	attacker->setFrameY(_round);
	LoadDeta();

	SOUNDMANAGER->play("scene2Theme", BGMVOLUME);

	return S_OK;
}

void Scene2::update()
{
	if (time <= 0.00001 && GateHp >= 0.00001)
	{
		gameover = true;
	}//게임 오버인지 알려준다.

	if (!gameover) // 진행중
	{
		if (time > 0)
			time -= TIMEMANAGER->getElapsedTime();

		if (distance >= 0.00001f)
		{
			player = RectMake(playerX, playerY, 50, 50);
			attackrect = RectMake(playerX + 20, playerY - 25 - attackrange, 10, 10);
			playerY -= 1.f;
			distance -= 1.f;

			mover->setFrameX(moverindex);
			movercount++;

			if (moverindex > mover->getMaxFrameX())
			{
				moverindex = 0;
			}
			else if (movercount % 20 == 0)moverindex++;
		}
		else
		{

			player = RectMake(playerX, playerY, 50, 50);
			attackrect = RectMake(playerX + 20, playerY - 25 - attackrange, 10, 10);


			attackUpdate();

			if (GateHp <= 0.00001f)
			{
				_round += 1;
				if (_round > 5)
				{
					SOUNDMANAGER->stop("scene2Theme");
					SCENEMANAGER->changeScene("EnddingScene");
				}
				else
				{
					if (_round != 5)
					{
						SOUNDMANAGER->stop("scene2Theme");
						SCENEMANAGER->changeScene("SchoolScene");
					}
					else
					{
						SCENEMANAGER->changeScene("EnddingScene");
					}
				}
			}
			playerFrame();
			attack();
		}

	}

	if (gameover)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SCENEMANAGER->changeScene("EnddingScene");
		}
	}

}

void Scene2::render()
{
	//IMAGEMANAGER->findImage("companyBackGround")->render(getMemDC());
	IMAGEMANAGER->findImage("NewBackGround")->render(getMemDC());
	if (_round == 0)
	{
		IMAGEMANAGER->findImage("background0")->render(getMemDC());
	}
	if (_round == 1)
	{
		IMAGEMANAGER->findImage("background1")->render(getMemDC());
	}
	if (_round == 2)
	{
		fixWallY = 200;
		playerY = playerY = CENTERY - 75 + fixWallY;
		doorrect = RectMake(210, 230 + fixWallY, 140, 70);
		IMAGEMANAGER->findImage("background2")->render(getMemDC());
	}
	if (_round == 3)
	{
		fixWallY = 200;
		playerY = playerY = CENTERY - 75 + fixWallY;
		doorrect = RectMake(210, 230 + fixWallY, 140, 70);
		IMAGEMANAGER->findImage("background3")->render(getMemDC());
	}
	if (_round == 4)
	{
		fixWallY = 200;
		playerY = playerY = CENTERY - 75 + fixWallY;
		doorrect = RectMake(210, 230 + fixWallY, 140, 70);
		IMAGEMANAGER->findImage("background4")->render(getMemDC());
	}
	if (_round == 5)
	{
		fixWallY = 200;
		playerY = playerY = CENTERY - 75 + fixWallY;
		doorrect = RectMake(210, 230 + fixWallY, 140, 70);
		IMAGEMANAGER->findImage("background5")->render(getMemDC());
	}

	//IMAGEMANAGER->findImage("Wall")->render(getMemDC(), 0, 450);
	//IMAGEMANAGER->findImage("dmgGate")->frameRender(getMemDC(), 207, 195 + fixWallY);
	//IMAGEMANAGER->findImage("MainGate")->frameRender(getMemDC(), 207 - fakex, 195 - fakey + fixWallY);
	if (GateHp >= 0.00001)
		IMAGEMANAGER->findImage("MainGate2")->frameRender(getMemDC(), 213, 195 + fixWallY);
	IMAGEMANAGER->findImage("hpBarBottom")->render(getMemDC(), 215, 160 + fixWallY);
	IMAGEMANAGER->findImage("hpBarTop")->render(getMemDC(), 215, 160 + fixWallY, 0, 0, GateHp*1.06, 10);
	//Rectangle(getMemDC(), player.left, player.top, player.right, player.bottom);
	IMAGEMANAGER->findImage("Wall")->render(getMemDC(), 0, 220 + fixWallY);
	//Rectangle(getMemDC(), doorrect.left, doorrect.top, doorrect.right, doorrect.bottom);
	//Rectangle(getMemDC(), Wallrect_left.left, Wallrect_left.top, Wallrect_left.right, Wallrect_left.bottom);
	//Rectangle(getMemDC(), Wallrect_right.left, Wallrect_right.top, Wallrect_right.right, Wallrect_right.bottom);

	if (distance >= 0.00001f)
	{
		IMAGEMANAGER->findImage("mover")->frameRender(getMemDC(), playerX, playerY);
	}
	else
	{
		IMAGEMANAGER->findImage("attacker")->frameRender(getMemDC(), playerX, playerY);
	}
	if (gameover) IMAGEMANAGER->findImage("gameover")->render(getMemDC(), 70, 340);


	char str[128];

	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "digital-7");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	sprintf_s(str, "TIME ATTACK : %4.2f", time);
	TextOut(getMemDC(), CENTERX - 100, 10, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);



	/*
	char str1[128];
	sprintf_s(str1, "공격력 : %f", attackdmg);
	TextOut(getMemDC(), 10, 30, str1, strlen(str1));

	char str2[128];
	sprintf_s(str2, "공격속도 : %f", attackspeed);
	TextOut(getMemDC(), 10, 50, str2, strlen(str2));*/

}

void Scene2::attack()
{
	float temp = m_fCreativity;
	/*while (temp > attackspeed / 100.f)
	{
	temp -= 100.f;
	attackspeed += 1.f;
	}
	*/
	attackspeed = temp / 100.f;

	attackspeed = 1.f / 10.f;


	AttackTime += TIMEMANAGER->getElapsedTime();
	if (AttackTime >= attackspeed)
	{
		AttackTime -= attackspeed;
		isattack = true;
		SOUNDMANAGER->play("hitsnd", SEVOLUME);
	}
}
void Scene2::KeyInPut()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		playerX -= 2.f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		playerX += 2.f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		playerY += 2.f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		playerY -= 2.f;
	}
	/*if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
	attack();
	}*/

}
void Scene2::attackUpdate()
{

	if (isattack)
	{

		int temp = 0;
		temp++;
		if (temp > 2)isattack = false;
		if (IntersectRect(&RectMake(0, 0, 0, 0), &attackrect, &doorrect))
		{
			//fakex = 5000;
			//fakey = 5000;

			MainGate2->setFrameX(1);
			GateHp -= attackdmg;
			isattack = false;
		}
		attackmotion = true;
		attacker->setFrameX(1);
	}
	else
	{
		if (attackmotion)
		{
			attacker = IMAGEMANAGER->findImage("attacker");
			if (indexdelay < 0)
			{


				if (index < 1)index++;
				else
				{
					index = 0;
					attackmotion = false;
				}
			}
			attacker->setFrameX(index);


		}
		else
		{
			attacker = IMAGEMANAGER->findImage("attacker");
		}

		MainGate2->setFrameX(0);
		attacker->setFrameX(0);
		fakex = 0;
		fakey = 0;
	}
}
void Scene2::GateFrameUpdate()
{

	if (GateHp < 66 && GateHp > 32)
	{
		MainGate->setFrameY(1);
		dmgGate->setFrameY(1);
	}
	else if (GateHp >= 1 && GateHp < 33)
	{
		MainGate->setFrameY(2);
		dmgGate->setFrameY(2);
	}
	else if (GateHp < 1)
	{
		MainGate->setFrameY(3);
		dmgGate->setFrameY(3);
	}
	else
	{
		MainGate->setFrameY(0);
		dmgGate->setFrameY(0);
	}
}
void Scene2::DontMove()
{
	if (IntersectRect(&RectMake(0, 0, 0, 0), &Wallrect_left, &player))
	{
		playerY += 2;
	}
	else if (IntersectRect(&RectMake(0, 0, 0, 0), &Wallrect_right, &player))
	{
		playerY += 2;
	}
	if (GateHp <= 0)dooropen = true;
	if (!dooropen)
	{
		if (IntersectRect(&RectMake(0, 0, 0, 0), &doorrect, &player))
		{
			playerY += 2;
		}
	}
}
void Scene2::LoadDeta()
{
	FILE *fp = NULL;
	fopen_s(&fp, "playerData.txt", "r");

	fscanf_s(fp, "%f", &m_fCreativity); // 공속
	fscanf_s(fp, "%f", &m_fFitness);    // 시간
	fscanf_s(fp, "%f", &m_fKnowledge);  // 공격력

	fclose(fp);

	attackdmg = (1.f + m_fKnowledge) / (_round * 2 + 1.f) / (_level * 2);
	attackspeed = 0.2f + m_fCreativity / 100;
	time = 10 + m_fFitness / 10;
}

void Scene2::playerFrame()
{
	/*attacker->setFrameX(index);
	count++;

	if (index > attacker->getMaxFrameX())
	{
	index = 0;
	}
	else if (count % 20 == 0)index++;*/

	/*if (isattack)
	{
	attacker->setFrameX(1);
	}
	else
	{
	attacker->setFrameX(0);
	}*/
}