#ifndef __PLAYER_SPRITE__
#define __PLAYER_SPRITE__

#include "cocos2d.h"
#include "BaseSprite.h"

class Player : public BaseSprite
{
public:
	Player();
	~Player();

	virtual bool init();

	CREATE_FUNC(Player);

	virtual void update();


	bool getInGravity();
	void setInGravity(bool i);

	bool getExitedGravity();
	void setExitedGravity(bool e);

	bool getOnGround();
	void setOnGround(bool i);

	void move();
	
	cocos2d::Vec2 getDirection();
	void setDirection(cocos2d::Vec2 d);

	cocos2d::Vec2 getGravity();
	void setGravity(cocos2d::Vec2 g);



	void setJetpack();
	void jetpack();

private:

	void onMouseDown(cocos2d::Event *event);

	//the vector used for movement on planets
	cocos2d::Vec2 direction;
	cocos2d::Vec2 gravity;
	cocos2d::Vec2 jetpackAcceleration;

	bool inGravity;
	bool onGround;

	//This boolean is used in the jetpack function in order to determine when to stop changing the direction of the
	//jetpack. This occurs when the player leaves the gravity field it started jetpacking in. This is reset when the player
	//first touches the ground of a planet again.
	bool exitedGravity;
};

#endif