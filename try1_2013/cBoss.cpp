#include "cBoss.h"

cBoss::cBoss() : cEnemy()
{
	maxHealthPoints = 100;
	healthPoints = maxHealthPoints;
	moovingSpeed = 10.0f; //THIS NEEDS TESTING
	fastMoovingSpeed = 25.0f; //THIS NEEDS TESTING
	doTeleport = false;

	//DEBUG THIS SHOULD BE FALSE!
	isSpawTriggered = false;

	debug = 0;

	actionSpeed = 300;

	bool speedUpped = false;
	bool teleporting = false;
	bool shrinked = false;

	enableAttack = true;
}


void cBoss::attachBulletList(vector<cBullet*> *theBullets)
{
	theBulletList = theBullets;
}

//move the model to the game area
void cBoss::spawn(float elapsedTime)
{
	if (isSpawTriggered)
	{
		float zPos = (moovingSpeed *2 ) * elapsedTime;
		cModel::m_mdlPosition.z -= zPos;

		if (cModel::m_mdlPosition.z < 35)
			isSpawTriggered = false;

		//terminate isSpawTriggered once in play area
	}

}

void cBoss::startLevel()
{
	gameScreen = boss;
	m_SoundMgr->getSnd("BossLvlInit")->playAudio(AL_TRUE);
	isSpawTriggered = true;

}

void cBoss::Die()
{
	enableAttack = false;

	m_SoundMgr->stopBGM();
	m_SoundMgr->getSnd("PlayerWins")->playAudio(AL_TRUE);
}

void cBoss::update(float elapsedTime)
{
	mdlDimensions tmp = {5.0f,5.0f,5.0f};
	cModel::setMdlDimensions(tmp);

	if (isSpawTriggered)
		spawn(elapsedTime);

	else
	{
		if (healthPoints < 11)
		{
			if (!shrinked)
			{
				//shrink
				mdlDimensions tmp = { 2.0f, 2.0f, 2.0f };
				cModel::setMdlDimensions(tmp);
				setMdlRadius(2.5f);
				setScale(glm::vec3(2.0f, 2.0f, 2.0f));
				m_SoundMgr->getSnd("BossShrink")->playAudio(AL_TRUE);

				shrinked = true;
			}

		}

		else if (healthPoints < 51)
		{
			if (!speedUpped)
			{
				//speed up
				moovingSpeed = fastMoovingSpeed;
				m_SoundMgr->getSnd("BossPoweUp")->playAudio(AL_TRUE);

				actionSpeed = 200;

				speedUpped = true;
			}
		}

		else if (healthPoints < 90)
		{
			if (!teleporting)
			{
				//start teleporting
				doTeleport = true;
				m_SoundMgr->getSnd("BossPoweUp")->playAudio(AL_TRUE);

				teleporting = true;
			}
		}
		else
		{

		}



		//move about + attack

		debug++;
		if (debug % actionSpeed == 0)
		{
			if ((rand() % 100 + 1) < 40)
				attack(elapsedTime);
			else
			{
				if ((rand() % 100 +1) < 50)
					teleport();
			}

			debug = 0;

		}


	}
}


void cBoss::attack(float elapsedTime)
{
	if (enableAttack)
	{
		//play attackSound
		m_SoundMgr->getSnd("BossFires")->playAudio(AL_TRUE);


		/*bullet*/
		glm::vec3 mdlBulletDirection;
		mdlBulletDirection.x = 0.0f;//-(float)glm::sin(glm::radians(this->getRotation()));
		mdlBulletDirection.y = 0.0f;// (float)glm::cos(glm::radians(this->getRotation()));
		mdlBulletDirection.z = -1.0f;//-(float)glm::sin(glm::radians(this->getRotation()));
		//mdlBulletDirection *= -1;

		// Add new bullet sprite to the vector array
		theBulletList->push_back(new cBullet);
		int numBullets = theBulletList->size() - 1;
		theBulletList->at(numBullets)->setDirection(mdlBulletDirection);
		theBulletList->at(numBullets)->setRotation(-90.0f);
		theBulletList->at(numBullets)->setScale(glm::vec3(0.4f, 0.4f, 0.4f));
		theBulletList->at(numBullets)->setSpeed(5.0f);
		theBulletList->at(numBullets)->setPosition(glm::vec3(this->getPosition().x, this->getPosition().y, this->getPosition().z - 2.0f) + mdlBulletDirection);
		theBulletList->at(numBullets)->setIsActive(true);
		theBulletList->at(numBullets)->update(elapsedTime);
		theBulletList->at(numBullets)->setMdlRadius(0.5f);

	}
}


/* 
VALID POSITIPON COORDINATES (x,y,z):

10,0,35
-10,0,35
7,0,5
-7,0,5

*/

void cBoss::teleport()
{
	if (doTeleport)
	{
		//rand() % 30 + 1985 the range 1985-2014
		float x = rand() % 4 + 7;
		float z = 5;

		if (x == 7)
			z = 5;
		else if (x == 8)
			z = 15;
		else if (x == 9)
			z = 25;
		else
			z = 35;


		if (rand() % 2 == 0)
			x = x*(-1);

		//play BOSS teleport sound
		m_SoundMgr->getSnd("BossTeleport")->playAudio(AL_TRUE);

		cModel::m_mdlPosition.x = x;
		cModel::m_mdlPosition.z = z;
	}

}



void cBoss::move(float elapsedTime)
{
	/*
	float xPos = 0;
	float zPos = 0;


	if (rand() % 10 == 0)
		xPos = (moovingSpeed / 4) * elapsedTime * getDirection().x;

	if (rand() % 10 == 0)
		zPos = (moovingSpeed / 4) * elapsedTime * getDirection().z;


	//maximum X boundary
	if ((m_mdlPosition.x + xPos) > 10 || (m_mdlPosition.x + xPos) < -10)
		setDirection(glm::vec3((getDirection().x * -1), (getDirection().y), getDirection().z));

	//maximum Z boundary
	if ((m_mdlPosition.z + zPos) > 35 || (m_mdlPosition.z + zPos) < 5)
		setDirection(glm::vec3((getDirection().x), (getDirection().y), getDirection().z * -1));

	
	//if (glm::normalize(cModel::m_mdlPosition.x))
	
	



	cModel::m_mdlPosition.x += xPos;
	cModel::m_mdlPosition.z += zPos;

	*/
}








cBoss::~cBoss()
{

}