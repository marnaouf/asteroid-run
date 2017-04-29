#ifndef __GRAVITY_SPRITE__
#define __GRAVITY_SPRITE__


#include "cocos2d.h"
#include "BaseSprite.h"

class Gravity : public BaseSprite
{
public:

	Gravity();
	~Gravity();
	virtual bool init();
	virtual void update();
	void spawn(float, float);
	void destroy();

	CREATE_FUNC(Gravity);

	

};


#endif