#ifndef _CPLAYER_H
#define _CPLAYER_H

#include "GameConstants.h"
#include "shootingRangeGame.h"
#include "cModel.h"
#include "cInputMgr.h"
#include "cCameraMgr.h"

class cPlayer : public cModel
{
private:
	cInputMgr* m_InputMgr;
	cCameraMgr* theCameraMgr;

public:
	cPlayer();
	void attachInputMgr(cInputMgr* inputMgr);
	void attachCameraMgr(cCameraMgr* cameraMgr);
	virtual void update(float elapsedTime);
	void switchToBossMode();
	int healthPoints;
	bool tookDamage;
	void Die();

	bool enableInput;

	~cPlayer();
};
#endif