#include "BaseSprite.h"

USING_NS_CC;

BaseSprite::BaseSprite() {}
BaseSprite::~BaseSprite(){}

bool BaseSprite::init()
{
	//init sprite
	if (!Sprite::init())
	{
		return false;
	}
	velocity = Vec2();
	acceleration = Vec2();
	friction = 0.0f;
	maxVelocity = 0.0f;
	maxVelocityEnabled = false;
	radius = 0.0f;
	active = false;
	prevPosition = getPosition();
	screenSize = Director::getInstance()->getVisibleSize();

	return true;
	
}



void BaseSprite::update()
{
	prevPosition = getPosition();
	float x = getPosition().x;
	float y = getPosition().y;
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;
	if (acceleration == Vec2())
	{
		auto length = velocity.length();
		length -= friction;
		velocity.normalize();
		velocity *= length;
	}
	if (maxVelocityEnabled)
	{
		if (velocity.lengthSquared() >= maxVelocity*maxVelocity)
		{
			velocity.normalize();
			velocity *= maxVelocity;
		}
	}
	setPosition(x + velocity.x, y + velocity.y);
	
}





const float& BaseSprite::getRadius() { return radius; }
void BaseSprite::setRadius(float r) { radius = r; }

const Vec2& BaseSprite::getVelocity() { return velocity; }
void BaseSprite::setVelocity(Vec2 v) { velocity = v; }

const Vec2& BaseSprite::getAcceleration() { return acceleration; }
void BaseSprite::setAcceleration(Vec2 a) { acceleration = a; }

const float& BaseSprite::getFriction() { return friction; }
void BaseSprite::setFriction(float f) { friction = f; }

const float& BaseSprite::getMaxVelocity() { return maxVelocity; }
void BaseSprite::setMaxVelocity(float m) { maxVelocity = m; }

const bool& BaseSprite::getMaxVelocityEnabled() { return maxVelocityEnabled; }
void BaseSprite::setMaxVelocityEnabled(bool b) { maxVelocityEnabled = b; }

const bool& BaseSprite::getActive() { return active; }
void BaseSprite::setActive(bool a) { active = a; }

const Vec2& BaseSprite::getPrevPosition() { return prevPosition; }



bool BaseSprite::checkCollision(BaseSprite* sprite)
{
	float r = sprite->getRadius();
	Vec2 pos = sprite->getPosition();
	float distance = getPosition().distance(pos);
	if (distance <= radius + r) return true;
	else return false;


}

Vec2 BaseSprite::getNormal(BaseSprite* sprite)
{
	Vec2 pos = sprite->getPosition();
	Vec2 normal;
	normal = pos - getPosition();
	normal.normalize();
	
	return normal;
}

const bool BaseSprite::offScreen()
{
	if (getPosition().x <-radius || getPosition().x > screenSize.width + radius || getPosition().y < -radius
		|| getPosition().y > screenSize.height + radius) return true;
	else return false;
}