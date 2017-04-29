#ifndef __PLANET_SPRITE__
#define __PLANET_SPRITE__


#include "cocos2d.h"
#include "BaseSprite.h"

class Planet : public BaseSprite
{
public:

	Planet();
	~Planet();
	virtual bool init();
	void spawn(float, float);
	void destroy();
	virtual void update();
	
	CREATE_FUNC(Planet);

	
	
};


#endif