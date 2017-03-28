#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	char image[256];

	//로딩해보자
	for ( int i = 0; i < 50; i++ )
	{
		memset( image, 0, sizeof( image ) );
		sprintf_s( image, "carrier%d", i );
		_loading->loadImage( image, "image/background.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB( 255, 0, 255 ) );
	}

	return S_OK;
}

void loadingScene::release()
{
	_loading->release();
	SAFE_DELETE( _loading );
}

void loadingScene::update()
{
	_loading->update();

	if ( !_loading->loadNext() )
	{
		SCENEMANAGER->changeScene( "ghost" );
	}
}

void loadingScene::render()
{
	_loading->render();
}
