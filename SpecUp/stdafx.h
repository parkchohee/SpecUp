// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN //MFC�� �ƴ� ���� ���α׷��� ���
							//WIN32_LEAN_AND_MEAN�� ������ commdlg.h ���
							//�ʿ���� ��������� ��Ŭ��� ���� �ʰ� ���ش�.

#include <Windows.h>		//������ ������� ��Ŭ���
#include <stdio.h>			//���Ĵٵ� ����� ��� ��Ŭ��� (printf, scanf ���)
#include <tchar.h>			//�����쿡�� ����� ���ڿ� ��� ��� ��Ŭ���
							//MBCS (Multi Byte Character Set)
							//->������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ�
							//WBCS (Wide Byte Character Set)
							//->��� ���ڸ� 2����Ʈ�� ó��. �����ڵ� ���
#include <vector>
#include <map>


#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "database.h"
#include "actionManager.h"
#include "keyAnimationManager.h"
#include "collision.h"
#include "soundManager.h"
//using namespace MY_UTIL;

/* ===== �����ι� ===== */
#define WINNAME (LPTSTR)(TEXT("SPEC UP!!!"))
#define WINSTARTX 10
#define WINSTARTY 0
#define WINSIZEX 540
#define WINSIZEY 780
#define CENTERX (WINSIZEX / 2)
#define CENTERY (WINSIZEY / 2)
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{if(p) { delete (p);		(p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) { delete[] (p);		(p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) { (p)->release();	(p) = NULL;}}

#define SEVOLUME 5.0f
#define BGMVOLUME 10.0f
/* =========== �̱��� =========== */
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define DATABASE database::getSingleton()
#define ACTIONMANAGER actionManager::getSingleton()
#define KEYANIMANAGER keyAnimationManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()

/* ===== ���� ���� ===== */
extern POINT _ptMouse;
extern HWND _hWnd;
extern HINSTANCE _hInstance;
extern bool _leftButtonDown;
extern bool _rightButtonDown;
extern int _level;
extern int _round;