#include "stdafx.h"
#include "cFirstScene.h"


cFirstScene::cFirstScene()
{
}


cFirstScene::~cFirstScene()
{
}

HRESULT cFirstScene::init()
{
	ZeroMemory(&m_stCtop, sizeof(m_stCtop));
	m_stCtop.img	= IMAGEMANAGER->findImage("CtoP");
	m_stCtop.alpha	= 255;
	m_stCtop.count	= 1;
	m_stCtop.spd	= 3;
	m_stCtop.x		= CENTERX - m_stCtop.img->getWidth() / 2;
	m_stCtop.y		= 625;
	m_stCtop.rc		= RectMake(m_stCtop.x, m_stCtop.y, m_stCtop.img->getWidth(), m_stCtop.img->getHeight());

	ZeroMemory(&m_stTitle, sizeof(m_stTitle));
	m_stTitle.img	 = IMAGEMANAGER->findImage("titleName");
	m_stTitle.alpha	 = 10;
	m_stTitle.count	 = 1;
	m_stTitle.spd	 = 5;
	m_stTitle.x		 = CENTERX - m_stTitle.img->getWidth() / 2;
	m_stTitle.y		 = -m_stTitle.img->getHeight();
	m_stTitle.rc	 = RectMake(m_stTitle.x, m_stTitle.y, m_stTitle.img->getWidth(), m_stTitle.img->getHeight());

	m_nDir = 1;

	SaveDatabase(); 

	SOUNDMANAGER->play("mainTheme", 10.f);

	return S_OK;
}

void cFirstScene::release()
{
}

void cFirstScene::update()
{
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		SOUNDMANAGER->stop("mainTheme");
		SCENEMANAGER->changeScene("OpeningScene");
	}

	MoveRect();
}

void cFirstScene::render()
{
	IMAGEMANAGER->findImage("firstBackground")->render(getMemDC());
	m_stCtop.img->alphaRender(getMemDC(), m_stCtop.rc.left, m_stCtop.rc.top, m_stCtop.alpha);
	m_stTitle.img->alphaRender(getMemDC(), m_stTitle.rc.left, m_stTitle.rc.top, m_stTitle.alpha);

	HFONT myFont = CreateFont(15, 0, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "도담9");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);

	TextOut(getMemDC(), 100, WINSIZEY - 50, "SGA 1604 박화용, 정다경, 안정욱, 박초희, 심용보", 
		strlen("SGA 1604 박화용, 정다경, 안정욱, 박초희, 심용보"));

	SetTextColor(getMemDC(), RGB(0, 0, 0));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

void cFirstScene::MoveRect()
{
	m_stCtop.count++;
	m_stTitle.count++;
	
	//click to play alpha
	if (m_stCtop.count % m_stCtop.spd == 0)
	{
		m_stCtop.alpha -= (15 * m_nDir);
		m_stCtop.count = 0;
	}

	if (m_stCtop.alpha < 0)
	{
		m_stCtop.alpha = 0;
		m_nDir *= -1;
	}
	else if (m_stCtop.alpha > 255)
	{
		m_stCtop.alpha = 255;
		m_nDir *= -1;
	}

	//title
	int endLine = CENTERY - m_stTitle.img->getHeight();
	if (endLine < (m_stTitle.rc.bottom + m_stTitle.rc.top) / 2) m_stTitle.isStop = true;
	
	if (!m_stTitle.isStop)
	{
		if (m_stTitle.count % m_stTitle.spd == 0)
		{
			m_stTitle.alpha += 5;
			m_stTitle.count = 0;
			m_stTitle.rc.top += 10;
			if (m_stTitle.alpha > 255) m_stTitle.alpha = 255;
		}
	}
	
}

void cFirstScene::SaveDatabase()
{
	FILE *fp = NULL;
	fopen_s(&fp, "playerData.txt", "w");

	fprintf_s(fp, "0.0 0.0 0.0");

	fclose(fp);
}
