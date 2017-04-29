#include "Gravity.h"
#include "math.h"

USING_NS_CC;

Gravity::Gravity() {}
Gravity::~Gravity(){}

bool Gravity::init()
{
	//similar to planet and player so check player comments
	if (!BaseSprite::init())
	{
		return false;
	}

	radius = 2.1*std::floor(std::sqrt(screenSize.width*screenSize.height / 50.0f / 3.1415f));
	

	auto image = DrawNode::create();
	image->drawDot(Vec2(0, 0), radius, Color4F(0,0,1,0.2f));
	this->addChild(image);

	//make invisible and not updateable
	setVisible(false);
	

	
	
	
	//set  node tag as 3, used for collision shit.
	this->setTag(3);


	return true;
}

void Gravity::spawn(float x, float y)
{
	setVisible(true);
	setActive(true);
	this->setPosition(x, y);
	setVelocity(Vec2(-screenSize.width/300, 0.0f));
	
	
}

void Gravity::destroy()
{
	setVisible(false);
	setActive(false);
	
	
}

void Gravity::update()
{
	BaseSprite::update();

	if (getPosition().x < -radius*2) destroy();
}