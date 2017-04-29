#ifndef __BASE_SPRITE__
#define __BASE_SPRITE__

#include "cocos2d.h"

//This is an extension of the normal Sprite class except with added handrolled physics
//and an added collision function thats based of a radius value each BaseSprite has (Basically all
//BaseSprites are circles cuz that what I need for this game)

class BaseSprite : public cocos2d::Sprite
{
public:
	BaseSprite();
	~BaseSprite();

	virtual bool init();

	CREATE_FUNC(BaseSprite);

	virtual void update();


	const float& getRadius();
	void setRadius(float r);

	const cocos2d::Vec2& getVelocity();
	void setVelocity(cocos2d::Vec2 v);

	const cocos2d::Vec2& getAcceleration();
	void setAcceleration(cocos2d::Vec2 a);

	const float& getFriction();
	void setFriction(float f);

	const float& getMaxVelocity();
	void setMaxVelocity(float m);

	const bool& getMaxVelocityEnabled();
	void setMaxVelocityEnabled(bool b);
	
	const bool& getActive();
	void setActive(bool a);

	const cocos2d::Vec2& getPrevPosition();

	const bool offScreen();
	

	//custom collision function for circles that uses position and radius of sprite
	bool checkCollision(BaseSprite* sprite);

	//finds normalized direction vector between self and other BaseSprite
	cocos2d::Vec2 getNormal(BaseSprite* sprite);



protected:

	float radius;
	cocos2d::Vec2 velocity;
	cocos2d::Vec2 acceleration;
	//make sure always positive.
	float friction;
	//make sure always positive.
	float maxVelocity;
	//disabled by default
	bool maxVelocityEnabled;

	//determines whether update is called or not.
	//for simplicity although its ugly the activity of the sprite is checked in GameScene
	//update
	bool active;

	cocos2d::Vec2 prevPosition;
	
	cocos2d::Size screenSize;
};

#endif