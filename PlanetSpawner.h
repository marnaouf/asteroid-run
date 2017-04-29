#ifndef __PLANET_SPAWNER__
#define __PLANET_SPAWNER__

#include "cocos2d.h"
#include "Planet.h"
#include "Gravity.h"

class PlanetSpawner
{
public:
	PlanetSpawner();
	~PlanetSpawner();
	void init(int);
	void addToScene(cocos2d::Layer*);
	void spawn(float, float);
	void update();

	void destroyAll();

	cocos2d::Vector<Planet*>::iterator getPlanetBegin();
	cocos2d::Vector<Planet*>::iterator getPlanetEnd();

	cocos2d::Vector<Gravity*>::iterator getGravityBegin();
	cocos2d::Vector<Gravity*>::iterator getGravityEnd();

private:
	cocos2d::Vector<Planet*> planetVector;
	cocos2d::Vector<Planet*>::iterator currentPlanet;

	cocos2d::Vector<Gravity*> gravityVector;
	cocos2d::Vector<Gravity*>::iterator currentGravity;
};

#endif