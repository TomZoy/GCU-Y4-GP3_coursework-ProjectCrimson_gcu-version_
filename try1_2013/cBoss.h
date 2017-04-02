#ifndef _CBOSS_H
#define _CBOSS_H

#include "GameConstants.h"
#include "cModel.h"
#include "cEnemy.h"

class cBoss : public cEnemy
{
public:
	cBoss();

	virtual void update(float elapsedTime);

	int healthPoints;
	~cBoss();


};
#endif