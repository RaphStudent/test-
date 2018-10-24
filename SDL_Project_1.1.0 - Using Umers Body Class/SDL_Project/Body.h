#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include "SDL.h"
#include "Collider.h"
#include "VMath.h"
using namespace MATH; 

class Body {
public:
	Vec3 pos;
	Vec3 vel; 
	float rad;
	friend class Collider;
private:
	Vec3 accel;
	float mass;
	bool isFloor;
	SDL_Surface *bodyImage;
	
public:
	Body(char* imageName ,float mass_,float rad_, Vec3 pos_, Vec3 vel_, Vec3 accel_);
	~Body();
	void Update(const float deltaTime,bool isFloor,bool isContained);
	void ApplyForce(Vec3 force);
	Vec3 ColiderMaths(Body body1, int E);
	Vec3 PlanetForce();
	Vec3 StarForce();
	/// Just a little helper function
	SDL_Surface* getImage();
};


#endif