#include "Player.h"
#include <random>
#include "math.h"


USING_NS_CC;

Player::Player(){}
Player::~Player(){}

bool Player::init()
{
	//init sprite
	if (!BaseSprite::init())
	{
		return false;
	}

	//radius for collision stuff
	radius = std::floor(std::sqrt(screenSize.width*screenSize.height / 50.0f / 3.1415f))/5;
	
	active = true;
	maxVelocityEnabled = true;
	
	//might have to make faster;
	setMaxVelocity(screenSize.width*screenSize.height/120000);
	direction = Vec2(0.2,0.5);
	gravity = Vec2();
	setOnGround(false);
	exitedGravity = false;

	//temporary graphics
	auto image = DrawNode::create();
	image->drawDot(Vec2(0, 0), radius, Color4F::MAGENTA);
	this->addChild(image);

	

	//set  node tag as 1, used for collision shit.
	//planet is 2 and gravity is 3
	this->setTag(1);


	auto mouselistener = EventListenerMouse::create();
	mouselistener->onMouseDown = CC_CALLBACK_1(Player::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouselistener, this);



	return true;
}


void Player::onMouseDown(Event *event)
{
	auto e = (EventMouse*)event;
	this->setPosition(Vec2(e->getLocationInView().x, screenSize.height+(e->getLocationInView().y)));
	setAcceleration(Vec2(0,0));
	setVelocity(Vec2(0,0));

}

void Player::update()
{
	
	if (onGround)
	{
		
		move();
	}
	
	BaseSprite::update();
	
	
}

void Player::move()
{
	setVelocity(direction*0.08f);
}

bool Player::getInGravity() { return inGravity; }
void Player::setInGravity(bool i) { inGravity = i; }

bool Player::getExitedGravity() { return exitedGravity; }
void Player::setExitedGravity(bool e) { exitedGravity = e; }

bool Player::getOnGround() { return onGround; }
void Player::setOnGround(bool i) { onGround = i; }

Vec2 Player::getDirection() { return direction; }
void Player::setDirection(Vec2 d) { direction = d; }

Vec2 Player::getGravity() { return gravity; }
void Player::setGravity(Vec2 g) { gravity = g; }


//currently not being used
void Player::setJetpack()
{
	jetpackAcceleration = direction.rotateByAngle(Vec2(), 3.1415/ 2).getNormalized();
}

void Player::jetpack()
{
	//acceleration = direction.rotateByAngle(Vec2(), 3.1415/ 2)*0.005;
	if (!exitedGravity && !inGravity) exitedGravity = true;

	if (!exitedGravity) acceleration = -gravity*0.6;
	
}