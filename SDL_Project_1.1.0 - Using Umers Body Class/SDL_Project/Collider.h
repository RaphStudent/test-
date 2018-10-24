#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector.h"
class Collider
{
public:
	friend class Body;
	static bool CheckCollision(Body *body1_, Body *body2_);
	static void HandleCollision(Body *body1_, Body *body2_, float E_);
	Collider();
	~Collider();
	
};
#endif