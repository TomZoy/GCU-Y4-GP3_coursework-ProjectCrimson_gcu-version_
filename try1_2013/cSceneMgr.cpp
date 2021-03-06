/*
==================================================================================
cSceneMgr.cpp
==================================================================================
*/

#include "cSceneMgr.h"
#include "GameConstants.h"

cSceneMgr* cSceneMgr::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cSceneMgr::cSceneMgr()
{

}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSceneMgr* cSceneMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSceneMgr();
	}

	return cSceneMgr::pInstance;
}




void cSceneMgr::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}



void cSceneMgr::takeInput()
{



	switch (gameScreen)
	{
	case intro:
		if (m_InputMgr->isKeyDown('N'))
		{
			gameScreen = guide;
		}


		break;
	case guide:
		if (m_InputMgr->isKeyDown('N'))
		{
			gameScreen = game;
		}

		break;
	case game:



		break;
	case gameOver:
		if (m_InputMgr->isKeyDown('N'))
		{
			gameScreen = quitGame;
		}
		break;
	default:
		break;
	}






}



cSceneMgr::~cSceneMgr()
{

}
