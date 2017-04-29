#define COCOS2D_DEBUG 1
#include "PlanetSpawner.h"


USING_NS_CC;

PlanetSpawner::PlanetSpawner(){}
PlanetSpawner::~PlanetSpawner(){}

void PlanetSpawner::init(int length)
{
	
	
	this->planetVector = Vector < Planet* >(length);
	this->gravityVector = Vector<Gravity*>(length);
	for (length; length > 0; --length)
	{
		this->planetVector.pushBack(Planet::create());
		this->gravityVector.pushBack(Gravity::create());
	}
	currentPlanet = planetVector.begin();
	currentGravity = gravityVector.begin();

	
}

void PlanetSpawner::addToScene(Layer* scene)
{
	for (auto gravity : this->gravityVector)
	{
		scene->addChild(gravity);
	}
	for (auto planet: this->planetVector)
	{
		scene->addChild(planet);
	}
	
}

void PlanetSpawner::spawn(float x, float y)
{
	
	
	(*currentGravity)->spawn(x,y);
	if (currentGravity == gravityVector.end()-1) currentGravity = gravityVector.begin();
	else ++currentGravity;
	
	
	(*currentPlanet)->spawn(x,y);
	if (currentPlanet == planetVector.end() - 1) currentPlanet = planetVector.begin();
	else ++currentPlanet;
	
}

void PlanetSpawner::destroyAll()
{
	auto p = planetVector.begin();
	auto g = gravityVector.begin();
	while (p != planetVector.end())
	{
		if ((*p)->getActive()) (*p)->destroy();
		if ((*g)->getActive()) (*g)->destroy();
		++p;
		++g;

	}
}

void PlanetSpawner::update()
{
	auto p = planetVector.begin();
	auto g = gravityVector.begin();
	while (p != planetVector.end())
	{
		if ((*p)->getActive()) (*p)->update();
		if ((*g)->getActive()) (*g)->update();
		++p;
		++g;
		
	}
}

cocos2d::Vector<Planet*>::iterator PlanetSpawner::getPlanetBegin() { return planetVector.begin();}
cocos2d::Vector<Planet*>::iterator PlanetSpawner::getPlanetEnd() { return planetVector.end(); }

cocos2d::Vector<Gravity*>::iterator PlanetSpawner::getGravityBegin() { return gravityVector.begin();}
cocos2d::Vector<Gravity*>::iterator PlanetSpawner::getGravityEnd() { return gravityVector.end();}