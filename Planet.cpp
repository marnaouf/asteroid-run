#include "Planet.h"
#include<functional>
#include "math.h"

Planet::Planet() {}
Planet::~Planet() {}

USING_NS_CC;

bool Planet::init()
{
	//pretty much all the same as player so check comments there
	if (!BaseSprite::init())
	{
		return false;
	}
	
	
	radius = std::floor(std::sqrt(screenSize.width*screenSize.height / 50.0f / 3.1415f));


	auto image = Sprite::create("ass.png");
	//image->drawDot(Vec2(0, 0), radius, Color4F::ORANGE);
	this->addChild(image);

	//make invisble and unupdateable
	setVisible(false);
	


	

	//set  node tag as 2, used for collision shit.
	this->setTag(2);




	return true;
}

void Planet::spawn(float x, float y)
{
	
	setVisible(true);
	setActive(true);
	this->setPosition(x, y);
	setVelocity(Vec2(-screenSize.width / 300, 0.0f));
	
}

void Planet::destroy()
{
	setVisible(false);
	setActive(false);
	setVelocity(Vec2(0.0f, 0.0f));
}

void Planet::update()
{
	BaseSprite::update();

	if (getPosition().x < -radius * 2) destroy();
}