#define COCOS2D_DEBUG 1



#include<stdio.h>
#include<time.h>
#include<stdlib.h>


#include "GameScene.h"



USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init() 
	
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//use my own variable so i can use it through out the class easily
	screenSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	//initialize random number generator
	srand(time(NULL));

	//init begin
	begin = false;

	//initialize planetSpawner
	planetSpawner = PlanetSpawner();
	planetSpawner.init(5);
	planetSpawner.addToScene(this);
	
	//initialize deathTimer, may need to change this to depend on current planetspeed
	deathTime = 1.5 * 60;
	deathTimer = deathTime;
	
	

	//may eventually need to change the priority of update and the input events
	
	scheduleUpdateWithPriority(2);
	
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//initiliaze player
	this->player = Player::create();
	this->addChild(player);
	setup();

	
	
	return true;
}

void GameScene::spawnPlanet(float dt)
{
	//the point of this is to make sure that there is variation in the spawns so we don't get
	//a lot of spawns very close to one another
	//Ill probably remove this or change it later.


	float y = random((*planetSpawner.getGravityBegin())->getRadius() , screenSize.height - (*planetSpawner.getGravityBegin())->getRadius());
	planetSpawner.spawn(screenSize.width +(*planetSpawner.getGravityBegin())->getRadius(),y);
	
	//to change value of timer u need to recall schedule on the same function.

	
	
}

void GameScene::setup()
{
	unschedule(schedule_selector(GameScene::spawnPlanet));
	planetSpawner.destroyAll();
	player->setAcceleration(Vec2());
	player->setVelocity(Vec2());
	player->setPosition(screenSize.width + (*planetSpawner.getGravityBegin())->getRadius(), screenSize.height / 2 - player->getRadius());
	jetpackON = false;
	settingJetpack = false;
	gravity = (*planetSpawner.getGravityBegin())->getRadius() / 100;
	planetSpawner.spawn(screenSize.width + (*planetSpawner.getGravityBegin())->getRadius(), screenSize.height / 2);
	
	deathTimer = deathTime;
	begin = false;
}

void GameScene::update(float delta)
{
	if (begin)
	{
		player->setAcceleration(Vec2());
		player->setInGravity(false);
		auto currentPlanet = planetSpawner.getPlanetBegin();
		auto currentGravity = planetSpawner.getGravityBegin();

		while (currentGravity != planetSpawner.getGravityEnd())
		{

			if ((*currentGravity)->getActive() && player->checkCollision((*currentGravity)))
			{
				Vec2 normal = player->getNormal((*currentGravity));
				auto pos = player->getPosition();
				player->setPosition(pos.x + (*planetSpawner.getGravityBegin())->getVelocity().x, pos.y);
				player->setAcceleration(normal*gravity);
				player->setInGravity(true);
				player->setGravity(normal*gravity);

			}


			++currentGravity;
		}


		//currently setJetpack does nothing
		if (settingJetpack)
		{
			player->setJetpack();
			settingJetpack = false;
		}
		if (jetpackON)
		{
			player->jetpack();
			log("%f", player->getVelocity().y / player->getVelocity().x);

		}


		//dunno how important order of updates is. in prototype its gravity, player, planet do not know 
		//if this matters so currently gonna just make it player and then planet then gravity.
		if (player->getActive()) player->update();

		player->setOnGround(false);
		while (currentPlanet != planetSpawner.getPlanetEnd())
		{

			if ((*currentPlanet)->getActive() && player->checkCollision((*currentPlanet)))
			{
				//While this seems to work there is a flaw in this logic that may become evident in some scenarios
				//when the jetpack becomes involved. In the future fix this asshole

				player->setVelocity(Vec2());
				Vec2 normal = player->getNormal((*currentPlanet));
				normal *= (player->getRadius() + (*currentPlanet)->getRadius());
				player->setPosition((*currentPlanet)->getPosition() - normal);
				player->setOnGround(true);

				player->setDirection(normal.rotateByAngle(Vec2(), 3.1415 / 2));



			}

			++currentPlanet;

		}

		planetSpawner.update();
		if (player->offScreen()) --deathTimer;
		else if (deathTimer != deathTime) deathTimer = deathTime;

		if (deathTimer <= 0) setup();
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* e)
{
	switch(keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		
		if (begin)
		{
			jetpackON = true;
			settingJetpack = true;
		}
		else
		{
			begin = true;
			schedule(schedule_selector(GameScene::spawnPlanet), 2.2f);
		}
		break;
	}
	
		
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* e)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		jetpackON = false;
		if (player->getExitedGravity()) player->setExitedGravity(false);
		break;
	}
}

bool GameScene::onTouchBegan(Touch* touch, Event* e)
{
	if (begin)
	{
		jetpackON = true;
		settingJetpack = true;
	}
	else
	{
		begin = true;
		schedule(schedule_selector(GameScene::spawnPlanet), 2.8f);
	}
	return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* e)
{
	jetpackON = false;
	if (player->getExitedGravity()) player->setExitedGravity(false);
}


