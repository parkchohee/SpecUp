#include "stdafx.h"
#include "gameStudy.h"

#include "cFirstScene.h"
#include "cOpening.h"
#include "cSchoolScene.h"
#include "cSelectScene.h"
#include "cTutorialScene.h"
#include "Scene2.h"
#include "cEnddingScene.h"

gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init(true);

	// 이미지...
	IMAGEMANAGER->addImage("world_alpha", "image/world_alpha.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("desk", "image/desk.bmp", 100, 75, true, RGB(255,0,255));					// 학생책상
	IMAGEMANAGER->addImage("teacherDesk", "image/teacherDesk.bmp", 100, 150, true, RGB(255, 0, 255));	// 선생님책상
	IMAGEMANAGER->addImage("teacherDesk2", "image/teacherDesk2.bmp", 100, 100, true, RGB(255, 0, 255));	// 교탁
	IMAGEMANAGER->addImage("schoolBackground", "image/schoolBackground.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));	// 교탁
	
	IMAGEMANAGER->addImage("firstBackground", "image/firstBackground.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));	// 교탁


	IMAGEMANAGER->addImage("upMiss", "image/up_miss.bmp", 60, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("CtoP", "image/firstScene/click_to_play.bmp", 217, 31, true, RGB(255, 0, 255)); //첫 씬 클릭 투 플레이
	IMAGEMANAGER->addImage("titleName", "image/firstScene/title_name.bmp", 417, 297, true, RGB(255, 0, 255)); //첫 씬 타이틀 이름
	IMAGEMANAGER->addImage("졸업장", "image/졸업장.bmp", 540, 780, false, false);
	SOUNDMANAGER->addSound("mainTheme", "sound/Main_Theme.mp3", true, true);
	SOUNDMANAGER->addSound("schoolTheme", "sound/수업시간.mp3", true, true);
	SOUNDMANAGER->addSound("sleep", "sound/잠자기.mp3", false, true);
	SOUNDMANAGER->addSound("loud", "sound/장난치기.mp3", false, true);
	SOUNDMANAGER->addSound("study", "sound/공부하기.mp3", false, true);
	SOUNDMANAGER->addSound("scene2Theme", "sound/씬2.mp3", false, true);
	SOUNDMANAGER->addSound("hitsnd", "sound/씬2히트.mp3", false, true);
	
	// 선생님 이미지
	IMAGEMANAGER->addFrameImage("teacherStand", "image/teacherStand.bmp", 150, 100, 3, 1, true, RGB(255, 0, 255));

	// 유저 이미지
	IMAGEMANAGER->addFrameImage("player_idle", "image/player_idle.bmp", 200, 540, 2, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_fun", "image/player_fun.bmp", 400, 540, 4, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player_sleep", "image/player_sleep.bmp", 400, 540, 4, 6, true, RGB(255, 0, 255));

	// icon
	IMAGEMANAGER->addFrameImage("icon_f", "image/icon_food.bmp", 200, 75, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("icon_g", "image/icon_glasses.bmp", 200, 75, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("icon_w", "image/icon_watch.bmp", 200, 75, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("iMoticon", "image/imoticon.bmp", 180, 60, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sBubble", "image/sBubble.bmp", 240, 60, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("icon_eMark", "image/exclamationMark.bmp", 30, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("restartbtn", "image/restartbtn.bmp", 50, 50, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addImage("board", "image/board.bmp", 540, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("board2", "image/board2.bmp", 540, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("whiteboard", "image/white_board.bmp", 150, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btnPlay", "image/play_btn.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btnSleep", "image/sleep_btn.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btnStudy", "image/study_btn.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pressPlay", "image/play_press.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pressSleep", "image/sleep_press.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pressStudy", "image/study_press.bmp", 150, 150, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("sky1", "image/sky1.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sky2", "image/sky2.bmp", 400, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("selectMode", "image/selectMode.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pauseBtn", "image/pauseBtn.bmp", 50, 50, true, RGB(255, 0, 255));

	// 이미지
	IMAGEMANAGER->addFrameImage("man", "image/man.bmp", 150, 540, 3, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("woman", "image/woman.bmp", 150, 540, 3, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("teacher", "image/teacher.bmp", 300, 600, 3, 6, true, RGB(255, 0, 255));
	// logo
	IMAGEMANAGER->addImage("startLogo", "image/start.bmp", 400, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pauseLogo", "image/pause.bmp", 400, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("timeoutLogo", "image/timeout.bmp", 500, 150, true, RGB(255, 0, 255));

	//Company image
	IMAGEMANAGER->addImage("companyBackGround", "image/Scene2/companyBackGround.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("Wall", "image/Scene2/Wall.bmp", 540, 81, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background", "image/Scene2/background.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("background0", "image/Scene2/background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background1", "image/Scene2/background1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background2", "image/Scene2/background2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background3", "image/Scene2/background3.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background4", "image/Scene2/background4.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background5", "image/Scene2/background5.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("NewBackGround", "image/Scene2/NewBackGround.bmp", WINSIZEX, WINSIZEY, false, false);
	IMAGEMANAGER->addImage("gameover", "image/Scene2/gameover.bmp", 400, 100, true, RGB(255, 0, 255));

	//hpBar
	IMAGEMANAGER->addImage("hpBarBottom", "image/hpBarBottom.bmp", 106, 10, false, false);
	IMAGEMANAGER->addImage("hpBarTop", "image/hpBarTop.bmp", 106, 10, false, false);

	// tuto
	IMAGEMANAGER->addImage("tuto1", "image/tuto/t2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto2", "image/tuto/t3.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto3", "image/tuto/t4.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto4", "image/tuto/t5.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto5", "image/tuto/t6.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto6", "image/tuto/t6.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto7", "image/tuto/t7.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto8", "image/tuto/t8.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto9", "image/tuto/t9.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto10", "image/tuto/t10.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto11", "image/tuto/t11.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto12", "image/tuto/t12.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto13", "image/tuto/t13.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto14", "image/tuto/t14.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tuto15", "image/tuto/t15.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	// testImage
	IMAGEMANAGER->addFrameImage("player", "image/test.bmp", 150, 90, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player2", "image/test2.bmp", 150, 90, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player3", "image/test3.bmp", 100, 90, 2, 1, true, RGB(255, 0, 255));
	
	// 씬 추가..
	SCENEMANAGER->addScene("FirstScene", new cFirstScene);
	SCENEMANAGER->addScene("OpeningScene", new cOpening);
	SCENEMANAGER->addScene("SchoolScene", new cSchoolScene);
	SCENEMANAGER->addScene("SelectScene", new cSelectScene);
	SCENEMANAGER->addScene("TutorialScene", new cTutorialScene);
	SCENEMANAGER->addScene("Scene2", new Scene2);
	SCENEMANAGER->addScene("EnddingScene", new cEnddingScene);

	// 처음 씬..
	SCENEMANAGER->changeScene("FirstScene");
	//SCENEMANAGER->changeScene("SchoolScene");
	//SCENEMANAGER->changeScene("Scene2");
	//SCENEMANAGER->changeScene("EnddingScene");
	return S_OK;
}

void gameStudy::release()
{
	gameNode::release();
}

void gameStudy::update()
{
	SCENEMANAGER->update();

	gameNode::update();
}

void gameStudy::render()
{
	//백버퍼에서 뿌려준다
	SetBkMode(getMemDC(), TRANSPARENT);
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//======================
	SCENEMANAGER->render();

	//======================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}


