#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PlanetSpawner.h"
#include "Player.h"
#include "Planet.h"

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	virtual void update(float delta);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* e);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* e);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e);

	

private:
	PlanetSpawner planetSpawner;
	void spawnPlanet(float dt);
	Player* player;
	bool jetpackON;
	bool settingJetpack;
	cocos2d::Size screenSize;
	float gravity;
	int deathTime;
	int deathTimer;

	//used to determine when the player has first clicked screen in order to start game
	bool begin;

	//used to setup game in case of restart, only temporary. will be replaced with a lose screen that has a reset button
	void setup();

	
	
};

#endif 
